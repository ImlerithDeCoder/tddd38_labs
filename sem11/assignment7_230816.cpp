#include <iostream>
#include <new>

//g++ -std=c++20 -Wall -Wextra -fsanitize=address -fsanitize=undefined min_kod.cpp

/*
 * operator new is used for constructing a object at a specific memory place provided
 * by the user. 
 * */

class ogaboga {
public:
  int oga = 10;
};

int main() {
  alignas(ogaboga) std::byte buffer[sizeof(ogaboga)];
  ogaboga* ptr = new(buffer) ogaboga;

  ptr->~ogaboga();

}
// no, we dont have do deleade, deleate needs only to be used when creating a object with the new operator.
// that is since placenent new does not allocate memory, it is given a memmory adress to contrict a object at.
// however we instead have do call the object destructor manualy.
