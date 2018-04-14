#include "Stack.h"
#include <iostream>


int main() {
  Stack<unsigned int>* s = new Stack<unsigned int>();
  for (unsigned int i = 0; i < 10; i++) {
    s->push(i);
  }
  try {
    for (unsigned int i = 0; i < 15; i++) {
      std::cout << s->pop() << std::endl;
    }
  }
  catch (StackEmptyException e) {
    e.printError();
  }
  return 0;
}