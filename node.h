#ifndef guard
#define guard
class node {
 public:
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
  node* left;
  node* right;
  char* data;
  node* next;
};

#endif
