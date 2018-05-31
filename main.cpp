#include <iostream>
#include "node.h"
#include "stack.h"
#include "queue.h"
#include <ctype.h>
#include <cstring>

queue* shunt(queue*, char*);
bool checkprecedence(char, char);
node* express(queue*);
void postfix(node*);
void prefix(node*);
void infix(node*);
void buildtree(stack*, node*);

using namespace std;

int main() {
  queue* postfixq = new queue();
  cout << "Welcome to the Shunting Yard!" << endl;
  cout << "Please enter an equation in infix notation" << endl;
  char* inf = new char [80];
  cin.getline(inf,80);
  postfixq = shunt(postfixq, inf);
  cout << "done with shunt" << endl;
  node* root = express(postfixq);
  cout << "done with express" << endl;
  bool running = true;
  while(running == true) {
    cout << "Do you want your equation in infix, prefix, or postfix notation, or do you want to quit?" << endl;
    char* trans = new char [80];
    cin.getline(trans, 80);
    if (strcmp(trans, "quit") == 0) {
      running = false;
    }
    else if (strcmp(trans, "infix") == 0) {
      infix(root);
      cout << endl;
    }
    else if (strcmp(trans, "postfix") == 0) {
      postfix(root);
      cout << endl;
    }
    else if (strcmp(trans, "prefix") == 0) {
      prefix(root);
      cout << endl;
    }
  }
}
void infix(node* parent) {
  cout << "(";
  if(parent -> getRight() != NULL) {//if there is right
    infix(parent -> getRight()); //runs for one to right
  }
  cout << parent -> getData();//prints the node data
  if (parent -> getLeft() != NULL) {//if left exists
    infix(parent -> getLeft());//runs for one to the left
  }
  cout << ")";
}
void prefix(node* parent) {
  cout << parent -> getData();//prints the node data 
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
  cout << parent -> getData();//prints the node data   
}
node* express(queue* postfixq){
  cout << "enterexpress" << endl;
  node* stackhead = postfixq -> dequeue();
  stackhead -> setNext(NULL);
  stack* treeconstr = new stack(stackhead);
  node* addstack = postfixq -> dequeue();
  while (addstack != NULL) {
    //cout << "a" << endl;
    addstack -> setNext(NULL);
    treeconstr -> push(addstack);
    //cout << "b" << endl;
    addstack = postfixq -> dequeue();
    //cout << "c" << endl;
  }
  node* root = treeconstr -> pop();
  //cout << "d" << endl;
  buildtree(treeconstr, root);
  return root;


  
  /*node* newNode = NULL;
  bool run = true;
  int nodenum = 0;
  int cur = 0;
  node** allnode = new node*[80];
  allnode[0] = head -> getNode();
  while(run == true) {
    if (head != NULL && head -> pop() != NULL){
      stack* curr = head;
      for (int i = 0; i <= cur; i++) {
	curr = curr -> pop();
      }
      if (curr == NULL) {
	break;
      }
      if(isdigit(curr -> getNode() -> getData()[0]) == true){
	newNode = curr -> pop() -> getNode();
        allnode [nodenum] = newNode;
	cur++;
	nodenum++;
	cout << nodenum;
      }
      else {
	node* op = new node(curr -> getNode() -> getData());
	op -> setLeft(allnode[nodenum-2]);
	op -> setRight(allnode[nodenum - 1]);
 	allnode[nodenum - 2] = op;
	allnode[nodenum - 1] = NULL;
	cur++;
	nodenum--;
      }
    }
    else {
      run = false;
    }
  }
  return allnode[0];*/ 
}

void buildtree(stack* treeconstr, node* parent) {
  cout << "buildtree" << endl;
  if (isdigit(parent -> getData()[0]) == true) {
    return;
  }
  node* leftchild = treeconstr -> pop();
  parent -> setLeft(leftchild);
  buildtree(treeconstr, leftchild);
  node* rightchild = treeconstr -> pop();
  parent -> setRight(rightchild);
  buildtree(treeconstr, rightchild);
}


queue* shunt(queue* postfixq, char* infix) {
  stack* opstack = NULL; //stack for operaters

#ifdef DEBUG
   cout <<"entering shunt" << endl;
#endif /* DEBUG */

  //??? idea for getting tokens out of infix
  // call a function get token that returns:
  // a null ended string
  // a type { operand, operator, rightparen, end }
  // rather than operator, it could be operator precedence (assign a level)
  // if type == operator
  //    put operator on postfixq
  // else if type == operator
  //    evaluate operator for precedence (you mispelled your function)
  //    and decide to push on opstack or hold, while you do some popping of the opstack
  //    and then push on opstack.
  // ??? I think this get token function will also need to receive and return the current index into
  // infix, because it will be reading from the starting index, evaluating what it reads while advancing
  // the index until it finds a complete token or finds a \0
  //  This will get rid of the for loop and instead it will be while not end of getting tokens from infix
  //???
  for(int i = 0; i < strlen(infix); i++) {//for length of input
    if(isdigit(infix[i]) == true) { //number goes on queue
	//builds array for data
	char* data = new char[80];
	bool run = true;
	int initi = i;
	data[0] = infix[i];
	while (run == true){
	  if (isdigit(infix[i+1])) {
	    i = i+1;
	    data[i - initi] = infix[i];
	  }
	  else{
	    run = false;
	  }
	}
	data[i+1] = '\0';
	
#ifdef DEBUG
	cout << "shunt1: operand =";
	cout << data[0] << endl;
#endif /* DEBUG */
	node* newNode = new node(data);
	postfixq -> enqueue(newNode);//makes queue tail the new node
    }
    else if (infix[i] == '(') {
      char* wa = new char[1];
      wa[0] = '(';
      wa[1] = '\0';
#ifdef DEBUG
      cout << "shunt2: operator =";
      cout << wa[0] << endl;
#endif /* DEBUG */
      node* n = new node(wa);
      if (opstack == NULL) {//Not declared yet
#ifdef DEBUG
	cout << "shunt3: create opstack1" << endl;
#endif /* DEBUG */
	opstack = new stack(n);
      }
      else{
	opstack -> push(n); //pushes the node onto stack
      }
    }
    else if (infix [i] == ')'){
      bool remove = false;
      while (remove == false){
	node* popped = opstack -> pop(); //pops off stack

#ifdef DEBUG
        cout << "shunt4: popped operator =";
        cout << popped -> getData()[0] << endl;
#endif /* DEBUG */
	if (popped -> getData()[0] != '(') { //if not reaching open paren
	  postfixq -> enqueue(popped); //enqueue
	}
	else {
	  remove = true; //else end
	}
      }
    }
    else { // operater goes on stack
      //??? I think push and pop should handle opstack NULL condition
      // so I don't think you need to check, plus this goes away if you create a get token function
      if (opstack == NULL) {
        //??? I think it should definitely be 2
	char* data = new char[2]; //might be [2]
        data[0] = infix[i];
        data[1] = '\0';
#ifdef DEBUG
        cout << "shunt5: operator =";
        cout << data[0] << endl;
#endif /* DEBUG */
	node* newNode = new node(data);
	//??? don't create a new opstack
#ifdef DEBUG
	cout << "shunt6: create opstack2" << endl;
#endif /* DEBUG */
	opstack = new stack(newNode);
      }
      else {
	/*stack* current = stackhead;
	while (current -> pop() != NULL){
	  current = current -> pop();
	  }*/
	char* data = new char[2];
	data[0] = infix[i];
	data[1] = '\0';
#ifdef DEBUG
        cout << "shunt7: operator =";
        cout << data[0] << endl;
#endif /* DEBUG */
	node* newNode = new node(data);
	//??? need to peek, not pop until you know the precendence
	node* tocompare = opstack -> pop();
#ifdef DEBUG
        cout << "shunt8: popped tocompare =";
        cout << tocompare -> getData()[0] << endl;
#endif /* DEBUG */
	//stack* stackend = new stack(newNode);
	bool prec = true;
	int count = 0;
	//if(tocompare != NULL){
#ifdef DEBUG
        cout << "shunt10: about to call checkprecedence() with data=";
        cout << data[0];
        cout << "and topcompare->getData()[0]=";
        cout << tocompare -> getData()[0] << endl;
#endif /* DEBUG */
	  prec = checkprecedence(data[0], tocompare -> getData()[0]);
	  //}
	  //else{
	  //prec = false;
	  //}
	if (prec == true) {
#ifdef DEBUG
          cout << "shunt11: queue tocompare" << endl;;
#endif /* DEBUG */
	  postfixq -> enqueue(tocompare);
	  count ++;
	  bool run = true;
	  while (run == true) {
	    //current = stackhead;
	    //while (current -> pop() != NULL){
	    //current = current -> pop();
	    //}
	    //if (current == stackhead) {
	    //run = false;
	    //}
	    node* putonque = opstack -> pop();
	    if(putonque == NULL) {
	      run = false;
	    }
	    else {
	      postfixq -> enqueue(putonque);
	      /*stack* trace = stackhead;
	      if (run == true) {
		while (trace -> pop() != current){
		current = current -> pop();
		}
		trace -> push(NULL);
		}*/
	    }
	  }	
	}
	if (count == 0) { //if nothing had to be removed
	  opstack -> push(tocompare);
	}
	opstack -> push(newNode);
      }
    }
  }
  bool run = true;
  while (run == true) {
    /*stack* current = stackhead;
    while (current -> pop() != NULL){
      current = current -> pop();
    }
    queuetail -> push(current);
    queuetail = current;
    if (current == stackhead) {
      run = false;
      stackhead = NULL;
    }
    if (run == true) {
      stack* trace = stackhead;
      while (trace -> pop() != current){
	//current = current -> pop();
	trace = trace -> pop();
	}
      trace -> push(NULL);
      }*/
    node* toen = opstack -> pop();
#ifdef DEBUG
    
    if (toen != NULL) {
      cout << "toen-> getData()[0] =";
      cout << toen -> getData()[0] << endl;
    }
#endif /* DEBUG */
    if (toen == NULL) {
      run = false;
    }
    else {
#ifdef DEBUG
    cout << "shunt12: about to enqueue toen" << endl;
#endif /* DEBUG */
      postfixq -> enqueue(toen);
    }
  }

#ifdef DEBUG
   cout <<"shunt13: about to print postfix queue" << endl;
#endif /* DEBUG */
  //??? for DEBUG? or is it required for assignment to print out postfix before asking user how they want their function?
  node* printing = postfixq -> getQueueHead();
  //??? walk the queue printing out the data without changing the queue?
  while (printing -> getNext() != NULL) {
    cout << printing -> getData();
    printing = printing -> getNext();
  }
  cout << printing-> getData() << endl;
#ifdef DEBUG
   cout <<"exiting shunt" << endl;
#endif /* DEBUG */
  return postfixq;
}

// returns true if existing is higher precedence than added
// returns false if existing is lower prececence or same precedence than added
bool checkprecedence(char added, char existing){
#ifdef DEBUG
   cout <<"enter checkprecedence" << endl;
#endif /* DEBUG */
  if((added == '-' || added == '+') && (existing == '*' || existing == '/' || existing == '^')) {
    return true;
  }
  else if ((added == '*' || added == '/') && existing == '^') {
    return true;
  }
  else {
#ifdef DEBUG
    cout <<"checkprecedence: return value false" << endl;
#endif /* DEBUG */
    return false;
  }
}
