#include "node.h"
class stack {
 public:
  stack(node*);
  ~stack();
  node* pop();
  void push(node*);
 private:
  node* stackhead;
};
