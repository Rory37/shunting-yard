#include "queue.h"
#include <iostream>

using namespace std;

queue :: queue() {//constructor
  queuehead = NULL;
  queuetail = NULL;
}

queue :: ~queue(){ //destructor
  delete queuehead;
  delete queuetail;
}

node* queue :: getQueueHead() {//will return head of ques
  return queuehead;
}

node* queue :: getQueueTail() {//wil return tail of queue
  return queuetail;
}

node* queue :: dequeue() {//takes one node off beggining of queue
  node* toreturn = queuehead;
  if(queuehead != NULL) {//prevents segfault
    queuehead = queuehead -> getNext();
  }
  if (queuehead == NULL) { //queue was emptied, tail taken off
    queuetail = NULL;
  }
  return toreturn;
}

void queue :: enqueue(node* toadd) {//adds to end of queue
  if (queuetail != NULL) {//if queue is made
    queuetail -> setNext(toadd);//adds to end
    queuetail = toadd;//updates tail
  }
  else {
    //makes first node the added
    queuehead = toadd;
    queuetail = toadd;
  }
}
