#include <cassert>
#include <memory>
#include <utility>
#include <string>
#include <vector>
#include <new>
#include <type_traits>


/* Implement Optional here */
template <typename T>
class Optional {
public:
  Optional() = default;

  template <typename U, typename = std::enable_if_t<!std::is_same_v<std::remove_cvref_t<U>, Optional>>>
  Optional(U&& i) { // default constructor, r-value och l-value
    set_item(std::forward<U>(i));
  }

  Optional(Optional<T> const& other) { // copy constructor, right?
    if (other.valid) {
      set_item(other.get_value());
    }
  }

  ~Optional() { //destructor
    clear();
  }

 Optional<T>& operator=(Optional<T> const& other) { // copy assigment operator
    if (this == &other) {
      return *this;
    }
    if (other.valid) {
      set_item(other.get_value());
    } else {
      clear();
    }
    return *this;
  }

  template <typename U, typename = std::enable_if_t<!std::is_same_v<std::remove_cvref_t<U>, Optional>>>
  Optional& operator=(U&& i) {
    set_item(std::forward<U>(i));
    return *this;
  }

  bool is_valid() {
    return valid;
  }


  T& get_value() {
    return *std::launder(reinterpret_cast<T*>(item)); // here we need std::launder because we need to cast the char pointer to a T pointer? right?
  }

  T const& get_value() const {
    return *std::launder(reinterpret_cast<T const*>(item));
  }


 void clear() {
    if (valid) {
      std::destroy_at(std::launder(reinterpret_cast<T*>(item)));
      valid = false;
    }
  }

private:

  template <typename U>
  void set_item(U&& i) {
    clear();
    new (item) T(std::forward<U>(i)); // kallar T konstruktor av i
    valid = true;
  }

  alignas(T) char item[sizeof(T)];
  bool valid{ false };
};






int main()
{
  
    {
        Optional<int> o { };
        assert( !o.is_valid() );

        o = 5;
        assert( o.is_valid() );
        assert( o.get_value() == 5 );

        // test that a reference is returned
        o.get_value() = 3;
        assert( o.get_value() == 3 );

        o.clear();
        assert( !o.is_valid() );
    }

  
    {
        // save a large std::string
        Optional<std::string> o { std::string(1000, '-') };

        assert( o.is_valid() );
        assert(( o.get_value() == std::string(1000, '-') ));

        auto previous_capacity = o.get_value().capacity();

        // here the destructor of the stored string must be called...
        o.clear();
        assert( !o.is_valid() );

        o = "";
        assert( o.is_valid() );
        assert( o.get_value().empty() );

        // ... due to the destructor of the string having been called previously
        // the number of allocated bytes in the new string must be different.
        //
        // If this test fails that means you are still re-using the same string
        // object as the beginning of the testcase, this is incorrect.
        assert( o.get_value().capacity() != previous_capacity );
    }

    // test copy operations
    {
        Optional<std::vector<int>> o1 { std::vector<int> { 1, 2, 3 } };
        Optional<std::vector<int>> o2 { };

        Optional<std::vector<int>> o3 { o1 }; // copy o1
        Optional<std::vector<int>> o4 { o2 }; // copy o2

        assert( o3.is_valid() );
        assert( o3.get_value() == o1.get_value() );

        // make sure that the copied value is a deep copy
        assert( &o3.get_value() != &o1.get_value() );

        assert( !o4.is_valid() );

        // copy o1 into o4
        o4 = o1;

        assert( o4.is_valid() );
        assert( o4.get_value() == o1.get_value() );

        // make sure that the copied value is a deep copy
        assert( &o4.get_value() != &o1.get_value() );

        // create a new, different optional
        Optional<std::vector<int>> o5 { std::vector<int>{ 4, 5, 6, 7 } };

        // overwrite existing values
        o3 = o5;

        assert( o3.is_valid() );
        assert( o3.get_value() == o5.get_value() );

        // make sure that the copied value is a deep copy
        assert( &o3.get_value() != &o5.get_value() );

        // clear out previous value with empty optional
        o4 = Optional<std::vector<int>>{ };

        assert( !o4.is_valid() );
    }

}
