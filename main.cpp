// https://github.com/TRVRNB/CppHeap.git
// this is a heap binary tree, a simple data structure that might end up being surprisingly complicated to implement
#include <iostream>
#include <cmath> // for round()
// apparently i might not actually need nodes for this
using namespace std;

namespace heap_data {
  // i like to use a main namespace to share some variables between functions
  char version[10] = "1.0";
  unsigned int tree_size = 1; // triple this when you reach another max depth
  unsigned int tree[2] = {0}; // this is unwrapped, and index 1 will be treated as index 0
};
using namespace heap_data;


int add_to_next(int index, unsigned int num){
  // this is recursive, and will repeatedly go down the tree until it finds space
  // it won't look for the highest-available space, instead it will only look through 1 chain
  unsigned int parent_index = floor(index / 2);
  if ((parent_index != 0) && (tree[parent_index] < num)){ // parent isn't the first index, AND bigger than parent
    return -1; // this should only come up if there is no space, so it needs resizing
  }
  // from now on, assume the PARENT is valid!
  if (index * 2 <= tree_size){
    if ((tree[index*2] < num) && (tree[index*2 + 1] < num)){
      // both children are lower
      if (tree[index] == 0){ // check for empty space
	tree[index] = num;
	return 1; // success!
      }
    } else {
      // one or more children is higher, go down the tree
      return add_to_next(floor(index / 2), num);
    }
  } else {
    // this is the end of the chain! assuming it's empty (it should be?), this space should be good to use
    if (tree[index] == 0){
      tree[index] = num;
      return 1; // success
    }
  }
  return 0; // miscellaneous error
}


void add_to_tree(unsigned int num){
  // look for a valid spot, then add to the tree
  bool put_at_trunk = false;
  for (int i = 1; i < tree_size + 1; i++){
    if (tree[i] == 0){ // spot found
      int code = add_to_next(i, num);
      if (code == 1){ // success
	return;
      } else if (code == -1){
	put_at_trunk = true; // this needs to go at the top
      }
    }
  }
  // there isn't enough space, triple the tree's size
  tree_size *= 3;
  
}


int main(){
  cout << "Heap / Binary Tree - Version " << version << endl;
  return 0;
}
