#include "node.h"
class queue {
 public:
  //prototypes
  queue();
  ~queue();
  void enqueue(node*);
  node* getQueueHead();
  node* getQueueTail();
  node* dequeue();
 private:
  node* queuehead;//holds head
  node* queuetail;//holds tail
};
