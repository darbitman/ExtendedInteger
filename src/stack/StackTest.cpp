#include "Stack.h"
#include <iostream>


int main(int argc, char* argv[]) {
  Stack<unsigned int>* s = new Stack<unsigned int>();
  for (unsigned int i = 0; i < 10; i++) {
    s->push(i);
  }
  try {
    for (unsigned int i = 0; i < 15; i++) {
      s->peek();
      std::cout << s->pop() << std::endl;
    }
  }
  catch (const Exception& e) {
    e.printError();
  }
  delete s;
  return 0;
}
