#include <iterator>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <variant>
#include <vector>
#include <utility> // for std::forward


class JSON_Field;
using JSON_List = std::vector<JSON_Field>;

class JSON
{
public:

    JSON_Field& operator[](std::string const& key)
    {
        return fields[key];
    }

    JSON_Field const& operator[](std::string const& key) const
    {
        return fields.at(key);
    }

    void print(std::ostream& os, int indent = 0) const;

private:

    std::map<std::string, JSON_Field> fields { };

};

// Implement JSON_Field here
class JSON_Field {
public:
  JSON_Field() = default;

  template <typename T>
  JSON_Field(T&& oga) : item{ std::forward<T>(oga) } {};

  // the five
  ~JSON_Field() = default;
  JSON_Field(JSON_Field const& obj) = default; // copy constructor
  JSON_Field(JSON_Field&& obj) = default; // move constructor
  JSON_Field& operator=(JSON_Field const& other) = default; // copy assigment
  JSON_Field& operator=(JSON_Field&& other) = default; // move assignment

  template <typename T>
  JSON_Field& operator=(T&& stuff) {
    // vad händer ifall T inte är double JSON_List eller JSON???
    item = std::forward<T>(stuff);
    return *this;
  }

  void print(std::ostream& os, int indent = 0) const {

    if (item.index() == 0) {

      os << std::get<double>(item);
    } else if (item.index() == 1) {

      auto begin = std::begin(std::get<JSON_List>(item));
      auto end = std::end(std::get<JSON_List>(item));

      os << "[";
      if (begin != end) {

        (begin++)->print(os);

        std::for_each(begin, end, [&os](JSON_Field const& i) {
          os << ", ";
          i.print(os);
        });
      }

      os << "]";
    } else if (item.index() == 2) {

      std::get<JSON>(item).JSON::print(os, indent);
    }
  }

private:
  std::variant<double, JSON_List, JSON> item;
};

void JSON::print(std::ostream& os, int indent) const
{
    os << "{" << std::endl;

    bool first { true };
    for (auto&& [key, value] : fields)
    {
        // print a 
        if (first)
        {
            first = false;
        }
        else
        {
            os << "," << std::endl;
        }

        os << std::setw(indent + 4) << "";
        os << '"' << key << "\" : ";
        value.print(os, indent + 4);
    }
    os << std::endl << std::setw(indent) << "" << "}";
}

int main()
{
    JSON json1;
    json1["d"] = 0.0;
    json1["e"] = 6.0;

    JSON json2;
    json2["a"] = 5.0;
    json2["b"] = JSON_List{ 1.0, JSON_List{ 2.0, 3.0 }, 4.0 };
    json2["c"] = std::move(json1);

    json2.print(std::cout);
    std::cout << std::endl;

    std::cout << "====" << std::endl;
    JSON json3;
    json3["list"] = JSON_List{ 0.5, std::move(json2), 1.5 };
    json3["number"] = -1.5;

    json3.print(std::cout);
    std::cout << std::endl;
}
