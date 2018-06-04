#include <iostream> //includes
#include "node.h"
#include "stack.h"
#include "queue.h"
#include <ctype.h>
#include <cstring>
//function prototypes
queue* shunt(queue*, char*);
bool checkprecedence(char, char);
node* express(queue*);
void postfix(node*);
void prefix(node*);
void infix(node*);
void buildtree(stack*, node*);

using namespace std;

int main() {
  queue* postfixq = new queue();//will hold all numbers
  cout << "Welcome to the Shunting Yard!" << endl;
  cout << "Please enter an equation in infix notation" << endl;
  char* inf = new char [80];
  cin.getline(inf,80);
  postfixq = shunt(postfixq, inf); //runs shunting yard with input
  node* root = express(postfixq);//builds tree
  bool running = true;
  while(running == true) {
    cout << "Do you want your equation in infix, prefix, or postfix notation, or do you want to quit?" << endl;
    char* trans = new char [80];//holds command
    cin.getline(trans, 80);
    if (strcmp(trans, "quit") == 0) {
      running = false;//exits program
    }
    else if (strcmp(trans, "infix") == 0) {
      infix(root);//prints infix notation
      cout << endl;
    }
    else if (strcmp(trans, "postfix") == 0) {
      postfix(root);//prints postfix notation
      cout << endl;
    }
    else if (strcmp(trans, "prefix") == 0) {
      prefix(root);//print prefix notation
      cout << endl;
    }
  }
}
void infix(node* parent) {
  cout << "(";//remove if too distracting, but messes with order of opp
  if(parent -> getRight() != NULL) {//if there is right
    infix(parent -> getRight()); //runs for one to right
  }
  cout << parent -> getData();//prints the node data
  if (parent -> getLeft() != NULL) {//if left exists
    infix(parent -> getLeft());//runs for one to the left
  }
  cout << ")";//remove if too distracting, but messes with order of opp
}
void prefix(node* parent) {
  cout << parent -> getData() << " ";//prints the node data 
  if(parent -> getRight() != NULL) {//if there is right
    prefix(parent -> getRight()); //runs for one to right
  }
  if (parent -> getLeft() != NULL) {//if left exists
    prefix(parent -> getLeft());//runs for one to the left
  }
}
void postfix(node* parent) {
  if(parent -> getRight() != NULL) {//if there is right
    postfix(parent -> getRight()); //runs for one to right
  }
  if (parent -> getLeft() != NULL) {//if left exists
    postfix(parent -> getLeft());//runs for one to the left
  }
  cout << parent -> getData() << " ";//prints the node data   
}
node* express(queue* postfixq){
  node* stackhead = postfixq -> dequeue(); //takes first off queue
  stackhead -> setNext(NULL);//makes sure that the next is null and not what was in the queue
  stack* treeconstr = new stack(stackhead); //makes new stack with the head
  //puts queue into stack
  node* addstack = postfixq -> dequeue();
  while (addstack != NULL) {
    addstack -> setNext(NULL);
    treeconstr -> push(addstack);
    addstack = postfixq -> dequeue();
  }
  node* root = treeconstr -> pop();//starts with last on stack
  buildtree(treeconstr, root);//runs the tree building function
  return root;
}

void buildtree(stack* treeconstr, node* parent) {
  if (isdigit(parent -> getData()[0]) == true) { //must be leaf
    return;
  }
  node* leftchild = treeconstr -> pop();//gets the left child of node
  parent -> setLeft(leftchild);
  buildtree(treeconstr, leftchild);//builds tree with left child 
  node* rightchild = treeconstr -> pop();//gets right child
  parent -> setRight(rightchild);
  buildtree(treeconstr, rightchild);//builds tree with right child
}


queue* shunt(queue* postfixq, char* infix) {
  stack* opstack = NULL; //stack for operaters
  for(int i = 0; i < strlen(infix); i++) {//for length of input
    if(isdigit(infix[i]) == true) { //number goes on queue
	//builds array for data
	char* data = new char[80];
	bool run = true;
	int initi = i;
	data[0] = infix[i];
	while (run == true){//all digits of one number into a separate array
	  if (isdigit(infix[i+1])) {
	    i = i+1;
	    data[i - initi] = infix[i];
	  }
	  else{
	    run = false;//got full number
	  }
	}
	data[i+1] = '\0';
	node* newNode = new node(data);//makes node with data
	postfixq -> enqueue(newNode);//adds node to queue
    }
    else if (infix[i] == '(') {//if starting paren
      char* wa = new char[1];
      wa[0] = '(';
      wa[1] = '\0';
      node* n = new node(wa);
      if (opstack == NULL) {//Not declared yet(starts with paren)
	opstack = new stack(n);
      }
      else{
	opstack -> push(n); //pushes the node onto stack
      }
    }
    else if (infix [i] == ')'){//end of parens
      bool remove = false;
      while (remove == false){
	node* popped = opstack -> pop(); //pops off stack
	if (popped -> getData()[0] != '(') { //if not reaching open paren
	  postfixq -> enqueue(popped); //enqueue
	}
	else {
	  remove = true; //else end
	}
      }
    }
    else { // operater goes on stack
      if (opstack == NULL) {//no stack yet
	//puts operator into array
	char* data = new char[2]; 
        data[0] = infix[i];
        data[1] = '\0';
	node* newNode = new node(data);//makes node
	opstack = new stack(newNode);//makes new stack
      }
      else {
	//puts opperator in array
	char* data = new char[2];
	data[0] = infix[i];
	data[1] = '\0';
	node* newNode = new node(data);//makes node
	node* tocompare = opstack -> pop();//takes off stack to compare for precedence
	bool prec = true;
	int count = 0;
	prec = checkprecedence(data[0], tocompare -> getData()[0]);//runs the checking of precedence
	if (prec == true) {//if the added is lower precendence
	  postfixq -> enqueue(tocompare);//adds to queue
	  count ++;
	  bool run = true;
	  //goes through rest of stack to check
	  while (run == true) {
	    count ++;
	    node* putonque = opstack -> pop();
	    if(putonque == NULL) {//if stack is empty
	      run = false;
	    }
	    else if (checkprecedence(data[0], putonque -> getData()[0]) == false) {//if priority is lower than added
	      opstack -> push(putonque);//puts the comparison back on stack
	      run = false;//exits loop
	    }
	    else {
	      postfixq -> enqueue(putonque);//adds on queue
	    }
	  }	
	}
	if (count == 0) { //if nothing had to be removed
	  opstack -> push(tocompare);
	}
	opstack -> push(newNode);//adds to stack
      }
    }
  }
  //once done with all additions
  bool run = true;
  while (run == true) {//run untill all stack popped
    node* toen = opstack -> pop();//takes off stack
    if (toen == NULL) {
      run = false;
    }
    else {
      postfixq -> enqueue(toen);//adds to queue
    }
  }
  return postfixq;//returns queue
}

// returns true if existing is higher precedence than added
// returns false if existing is lower prececence or same precedence than added
bool checkprecedence(char added, char existing){
  if((added == '-' || added == '+') && (existing == '*' || existing == '/' || existing == '^')) {//higher precedence
    return true;
  }
  else if ((added == '*' || added == '/') && existing == '^') {//higher precedence
    return true;
  }
  else if((added == '-' || added == '+') && (existing == '-' || existing == '+')) {//left associativity
    return true;
  }
  else if((added == '/' || added == '*') && (existing == '/' || existing == '*')) {//left associativity
    return true;
  }
  else if (added == existing) {//left associativity
    return true;
  }
  else {
    return false;
  }
}
