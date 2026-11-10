#include <algorithm>
#include <cassert>
#include <iterator>
#include <map>
#include <vector>
#include <list>
#include <iterator>
//g++ -std=c++17 -Wall -Wpedantic  ./uppg5.cpp

template <typename Container, typename Compare>
class sorted_inserted_iterator
{
  // vad i hela friden är dessa till för???
  using value_type = void;
  using reference = void;
  using pointer = void;
  using difference_type = void;
  using iterator_category = std::output_iterator_tag;

private:
  Container container;
  Compare compare;

public:
  sorted_inserted_iterator(Container& container, Compare compare)
  {
    this.container = container;
    this.compare = compare;
  };

  reference operator*() {}
  reference opperator++() {
    return *this;
  }
  reference operator++(int) { // a dummy int so we know its the other ++ operator
    return this++;
  }
  referenc operator=(Value_type &const obj) {
    //TODO implement this one!
    return this;
  }
};

template<typename Container, typename Comp>
sorted_inserted_iterator<Container, Comp> sorted_inserter(Container& con, Comp comp = std::less) {

  return sorted_inserted_iterator<Container, Comp>(con, comp);
}



int main() {
    std::map<int, int> m { {1, 2}, {5, 6} };
    *sorted_inserter(m)++ = std::make_pair(3, 4);
    assert((m == std::map<int, int>{{1,2},{3,4},{5,6}}));
/*
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
  */
}
