#include <algorithm>
#include <iterator>
#include <vector>
#include <map>
#include <list>
#include <cassert>

/* Implement your classes here */
template <typename Container, typename Predicate_type>
class filter_iterator
{
public:
  using difference_type = void;
  using value_type = it::value_type;
  using pointer = Iter::pointer;
  using reference = Iter::reference;
  using iterator_category = Iter::input_iterator_tag;



  auto operator==() { }


private:
  filter_iterator(Container& con, Predicate_type pred) : container(con), predicate_type(pred) {}
  
  auto it begin;
  auto it end;
  auto 
};

template<typename Container, typename Predicate>
class filter {
public:
  filter<Container, Predicate>(Container& c, Predicate p) con(c), pred(p) {}
 


private:
  Container const& con;
  Predicate pred;
};

int main()
{
 {
    std::vector<int> arr = { -17, 1, -1, 5, 7, -2, 3 };
    std::vector<int> result{};
    for (auto n : filter(arr, [](auto n) { return n > 0; }))
    {
      result.push_back(n);
    }

    assert((result == std::vector<int>{1, 5, 7, 3}));
  }
  
  /*{
    std::map<std::string, int> m = { {"ABC", 123}, {"DEF", 45}, {"GHI", 6} };
    std::vector<std::pair<std::string, int>> result{};
    for (auto p : filter(m, [](auto p) { return p.second > 10; }))
    {
      result.push_back(p);
    }

    assert((result == std::vector<std::pair<std::string, int>>{{"ABC", 123}, {"DEF", 45}}));
  }

  {
    std::list<double> l = {3.5, 5.4, -1.0};
    std::vector<double> result{};
    for (auto x : filter(l, [](auto) { return false; }))
    {
      result.push_back(x);
    }

    assert(result.empty());
  }

  {
    std::vector<int> source { 1, 2, 3, 4, 5, 6 };
    std::vector<int> destination {0, 0, 0};
    filter f{source, [](auto n) { return n % 2 == 0; }};
    std::copy(f.begin(), f.end(), destination.begin());
  }

  {
    std::vector<std::string> v {"a", "bc", "def", "ghij"};
    filter f{v, [](auto&& str) { return str.size() == 3; }};
    assert(f.begin()->size() == 3);
  }*/
}
