
#include "node.h"
#include <iostream>
node :: node(char* newdata) {//constructor
  left = NULL;
  right = NULL;
  data = newdata;
  next = NULL;
}

node :: ~node() {//destructor
  left = NULL;
  right = NULL;
  data = NULL;
  next = NULL;
}

void node :: setLeft(node* newLeft) {//sets left
  left = newLeft;
}

void node :: setRight(node* newRight) {//sets right
  right = newRight;
}

void node :: setNext(node* newnext) {//sets next
  next = newnext;
}

node* node :: getLeft() {//gets left
  return left;
}

node* node :: getRight() {//gets right
  return right;
}

node* node :: getNext() {//gets next
  return next;
}

char* node :: getData() {//gets data
  return data;
}
