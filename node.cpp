#include <iostream>
#include <iostream>
#include "node.h"
using namespace std;
// functions for the node class

Node::Node(int n){
  // constructor
  data = n;
}

Node::~Node(){
  // destructor; the data should automatically go out of scope, since it's not dynamic or static
  cout << "Deleting node with data " << data << "..." << endl;
}

int Node::getValue(){
  // just return the data
  return data;
}

Node* Node::getChild(int n){
  // returns child n
  if (n == 1){
    return child1;
  } else if (n == 2){
    return child2;
  } else {
    cout << "Invalid request for child " << n << "!" << endl;
    return nullptr; // this will only happen if i have an error in my code anyway
  }
}

int Node::getChildValue(int n){
  // returns data of child n
  if (n == 1){
    return child1->getValue();
  } else if (n == 2){
    return child2->getValue();
  } else {
    cout << "Invalid request for value of child " << n << "!" << endl;
    return 0;
  }
}

void Node::setChild(int n, Node* child){
  // replace one of your child's pointer; this should generally only replace nullptr unless used as a delete
  if (n == 1){
    child1 = child;
  } else if (n == 2){
    child2 = child;
  } else {
    cout << "Invalid request to replace child " << n << "!" << endl;
  }
  return;
}

void Node::setValue(int value){
  // replace your data with the new data
  data = value;
  // i might not ever need to use this, anyway
  return;
}
