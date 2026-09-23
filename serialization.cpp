#include <iostream>
#include <istream>
#include <limits>
#include <sstream>
using namespace std;

struct Product {
  string name;
  double price;
  int inventory;
};

ostream &operator<<(ostream &os, Product const &product) {
  return os << product.name << ": " << product.price << " kr ("
            << product.inventory << " available)";
}

template <typename T> T read(istream &is) {
  T data;
  is >> data;
  return data;
}

template <> string read<string>(istream &is) {
  string str;
  is.ignore(numeric_limits<streamsize>::max(), '#');
  getline(is, str, '#');
  return str;
}

template <> Product read<Product>(istream &is) {
  return {read<string>(is), read<double>(is), read<int>(is)};
}

template <typename T>
void write(ostream &os, T const &t) { os << t << ' '; }

template<>
void write<string>(ostream &os, string const &str)
{
  os << "#" << str << "#";
}

template<>
void write<Product>(ostream &os, Product const &obj) {
  write(os, obj.name);
  write(os, obj.price);
  write(os, obj.inventory);

}


int main() {
  stringstream ss;
  { // send data to ss
    Product apple{"Red Apple", 1.5, 100};
    Product laptop{"Laptop", 5995.0, 10};
    Product monitor{"4K Monitor", 8790.0, 1};
    write(ss, apple);
    write(ss, laptop);
    write(ss, monitor);
  }

  { // recieve data from ss
    Product apple{read<Product>(ss)};
    Product laptop{read<Product>(ss)};
    Product monitor{read<Product>(ss)};
    cout << apple << endl << laptop << endl << monitor << endl;
  }
}
