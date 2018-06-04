#include "stack.h"
#include <iostream>

using namespace std;

stack :: stack(node* newhead) { //constructor
  stackhead = newhead;
}

stack :: ~stack(){ //destructor
  delete stackhead;
}

node* stack :: pop() {//takes and returns last element off of stack
  node* current = stackhead;
  node* toreturn = NULL;
  if (current != NULL) {//if stack exitst
    while (current -> getNext() != NULL && current -> getNext() -> getNext() != NULL) {//checks 2 ahead to set next nul
      current = current -> getNext();
    }
    if (current -> getNext() != NULL) {//redundant
      toreturn = current -> getNext();
      current -> setNext(NULL);
    }
    else {//stackhead is only one
      toreturn = current;
      stackhead = NULL;
    }
  }
  return toreturn;//returns removed piece
}

void stack :: push(node* toadd) {//adds node to end of stack
  if (stackhead != NULL) {//if stack has items
    node* current = stackhead;
    while (current -> getNext() != NULL) {//goes to end of stack
      current = current -> getNext();
    }
    current -> setNext(toadd);//adds to end
  }
  else {
    stackhead = toadd;//makes stack with the added
  }
}
