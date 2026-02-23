#ifndef NODE
#define NODE
#include <iostream> // is this technically even necessary for headers?

class Node{
  // node for the binary tree. note that in this data structure,
  // the nodes don't "own" their children, so they won't ever call their child's destructor.
  // the only data that the node owns is its value (int)
 public:
  int getValue();
  Node* getChild(int n); // n = which child?
  int getChildValue(int n);
  void setChild(int n, Node* child);
  void setValue(int value);
  ~Node(); // destructor
  Node(int n); // constructor
 private:
  int data;
  Node* child1 = nullptr;
  Node* child2 = nullptr;
};

#endif
