
#include "node.h"
#include <iostream>
node :: node(char* newdata) {
  left = NULL;
  right = NULL;
  data = newdata;
  next = NULL;
}

node :: ~node() {
  left = NULL;
  right = NULL;
  data = NULL;
  next = NULL;
}

void node :: setLeft(node* newLeft) {
  left = newLeft;
}

void node :: setRight(node* newRight) {
  right = newRight;
}

void node :: setNext(node* newnext) {
  next = newnext;
}

node* node :: getLeft() {
  return left;
}

node* node :: getRight() {
  return right;
}

node* node :: getNext() {
  return next;
}

char* node :: getData() {
  return data;
}
