#include "node.h"
class queue {
 public:
  queue();
  ~queue();
  void enqueue(node*);
  node* getQueueHead();
  node* getQueueTail();
  node* dequeue();
 private:
  node* queuehead;
  node* queuetail;
};
