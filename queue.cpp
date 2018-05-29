#include "queue.h"
#include <iostream>

using namespace std;



queue :: queue() {
  queuehead = NULL;
  queuetail = NULL;

}

queue :: ~queue(){ //destructor
  delete queuehead;
  delete queuetail;
}

node* queue :: getQueueHead() {
  return queuehead;
}

node* queue :: getQueueTail() {
  return queuetail;
}

node* queue :: dequeue() {
  node* toreturn = queuehead;
  cout << "enter dequeue" << endl; /* DEBUG */
  if(queuehead != NULL) {//prevents segfault
    queuehead = queuehead -> getNext();
  }
  if (queuehead == NULL) { //queue was emptied, tail taken off
    queuetail = NULL;
  }
  return toreturn;
}

void queue :: enqueue(node* toadd) {
  cout << "enter enqueue" << endl; /* DEBUG */
  if (queuetail != NULL) {
    queuetail -> setNext(toadd);
    queuetail = toadd;
  }
  else {
    queuehead = toadd;
    queuetail = toadd;
  }
}
