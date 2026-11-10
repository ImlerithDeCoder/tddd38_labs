#include <algorithm>
#include <cassert>
#include <iterator>
#include <map>
#include <vector>
#include <list>
#include <iterator>
#include <functional>
#include <iostream>
//g++ -std=c++17 -Wall -Wpedantic  ./uppg5.cpp

template <typename Container, typename Compare = std::less<typename Container::value_type>>
class sorted_inserted_iterator
{
public:
  // vad i hela friden är dessa till för???
  using value_type = void;
  using reference = void;
  using pointer = void;
  using difference_type = void;
  using iterator_category = std::output_iterator_tag;


  sorted_inserted_iterator(Container& con, Compare com = {}) : container{con}, compare{com} {}

  sorted_inserted_iterator<Container, Compare>& operator*() { return *this; }
  sorted_inserted_iterator<Container, Compare>& operator++() { return *this; }
  sorted_inserted_iterator<Container, Compare>& operator++(int) { return *this; }// a dummy int so we know its the other ++ operator
  sorted_inserted_iterator<Container, Compare>& operator=(typename Container::value_type const& obj) {
    // vad sja den göra?
    // den ska hitta platsen den ska stoppa in obj på

    // den hittar itteratorn till första elementet som inte är mindre än obj (första elementet större än obj, right?)
    auto input_place = std::lower_bound(container.begin(), container.end(), obj, compare);

    // sedan ska den stoppa in den där
    
    //insert stoppar in obj på platsen efter itterator
    container.insert(input_place, obj);
    return *this;
  }

private:
  Container& container;
  Compare compare;


};

template <typename Container, typename Compare = std::less<typename Container::value_type>>
sorted_inserted_iterator<Container, Compare> sorted_inserter(Container& con, Compare comp = {}) {

  return sorted_inserted_iterator<Container, Compare>{con, comp};
}




int main() {
    std::map<int, int> m { {1, 2}, {5, 6} };
    *sorted_inserter(m)++ = std::make_pair(3, 4);
    assert((m == std::map<int, int>{{1,2},{3,4},{5,6}}));

    std::list<std::string> lst { "c" };
    *sorted_inserter(lst)++ = "a";
    *sorted_inserter(lst)++ = "b";
    *sorted_inserter(lst)++ = "a";
    assert((lst == std::list<std::string>{"a", "a", "b", "c"}));

    std::vector<int> v { 5, 7, 3, 12, -5 };

    {
      std::vector<int> res {};
      copy(std::begin(v), std::end(v), sorted_inserter(res));

      assert((res == std::vector<int>{-5, 3, 5, 7, 12 }));
    }

    {
      std::vector<int> res {};
      copy(std::begin(v), std::end(v),
            sorted_inserter(res, std::greater<int>{}));

      assert((res == std::vector<int>{12, 7, 5, 3, -5}));
    }

    {
      std::vector<int> res {};
      copy(std::begin(v), std::end(v),
            sorted_inserter<std::vector<int>, std::greater<int>>(res));
      assert((res == std::vector<int>{12, 7, 5, 3, -5}));
    }
  std::cout << "passed all tests!" << std::endl;
}
