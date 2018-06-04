#include "node.h"
class stack {
 public:
  //prototypes
  stack(node*);
  ~stack();
  node* pop();
  void push(node*);
 private:
  node* stackhead;//holds head of stack
};
