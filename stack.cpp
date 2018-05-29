#include "stack.h"
#include <iostream>

using namespace std;


stack :: stack(node* newhead) {
  stackhead = newhead;
}

stack :: ~stack(){ //destructor
  delete stackhead;
}

node* stack :: pop() {
  node* current = stackhead;
  node* toreturn = NULL;
#ifdef STACK_DEBUG
  cout << "enter pop" << endl;
#endif /* STACK_DEBUG */
  if (current != NULL) {
    while (current -> getNext() != NULL && current -> getNext() -> getNext() != NULL) {
      current = current -> getNext();
    }
    if (current -> getNext() != NULL) {
      toreturn = current -> getNext();
      current -> setNext(NULL);
    }
    else {//stackhead is only one
      toreturn = current;
      stackhead = NULL;
    }
  }
  return toreturn;
}

void stack :: push(node* toadd) {
#ifdef STACK_DEBUG
  cout << "enter push" << endl;
#endif /* STACK_DEBUG */
  if (stackhead != NULL) {
    node* current = stackhead;
    while (current -> getNext() != NULL) {
      current = current -> getNext();
      cout << "e" << endl;
    }
    current -> setNext(toadd);
  }
  else {
    stackhead = toadd;
  }
}
