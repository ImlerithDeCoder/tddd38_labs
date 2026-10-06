#include <iostream>

/* 
// fold expression solution
template <typename... Ts>
void print(Ts const&... args) {
    ((std::cout << args << " "), ...);
    std::cout << std::endl;
}*/


#include <sstream>

// variadi template solution
std::string print_helper() {
    return "";
}

template <typename First, typename... Ts>
std::string print_helper(First const& first, Ts const&... args) {
    std::ostringstream oss;
    oss << first << " " << print_helper(args...);
    return oss.str();
}

template <typename... Ts>
void print(Ts const&... args) {
  std::cout << print_helper(args...) << std::endl;
}


