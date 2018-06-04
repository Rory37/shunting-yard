#ifndef guard
#define guard
class node {
 public:
  //prototypes
  node(char*);
  ~node();
  void setLeft(node*);
  void setRight(node*);
  void setNext(node*);
  node* getLeft();
  node* getRight();
  node* getNext();
  char* getData();
 private:
  node* left;//holds left
  node* right;//holds right
  char* data;//hols data
  node* next;//holds next
};

#endif
