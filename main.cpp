// https://github.com/TRVRNB/CppHeap.git
// this is a heap binary tree, a simple data structure that might end up being surprisingly complicated to implement
#include <iostream>
#include <fstream>
#include <cmath> // for round()
#include <cstring> // for numerous functions (useless comment, i know)
#include <string>
// apparently i might not actually need nodes for this
// one major problem with this data structure i can think of off the top of my head, is that it doesn't handle collisions very well, especially near the bottom of the tree. 

using namespace std;


namespace heap_data {
  // i like to use a main namespace to share some variables between functions
  const char version[10] = "1.3";
  const unsigned int tree_size = 100; // this is extraneous and just exists to remind me
  unsigned int tree[101] = {0}; // this is unwrapped, and index 1 will be treated as index 0, since you can't double index 0 to get its children!
  // i could also just add 1 to the index when doing math, and it would have an absolutely negligible effect on both memory and performance, so why am i mentioning this?
};
using namespace heap_data;


int add_to_next(int index, unsigned int num){
  // REDO THIS FUNCTION! it has multiple errors now that i look it over, and doesn't even meet the requirements of the assignment
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
      // one or more children is higher, go up the tree
      return add_to_next(index * 2, num);
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


bool is_digit2(char c){
  // en.cppreference.com/w/cppp/string/byte/isdigit.html
  // this is just a more convenient std::isdigit, since it works with regular chars
  // and returns a bool instead of an int
  return isdigit(static_cast<unsigned char>(c));
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
  cout << "Couldn't find a spot! This either means you are out of space, or my code has a bug." << endl;
  return; // this probably means it ran out of space, but there won't be any resizing logic in this progam.
}


int main(){
  cout << "Heap / Binary Tree - Version " << version << endl;
  cout << "https://github.com/TRVRNB/CppHeap.git" << endl;
  cout << "Type 'HELP' for a list of commands." << endl;
  while (true){
    // QUIT breaks the loop
    cout << "$ " << flush;
    string input;
    cin >> input;
    if (input == "QUIT"){ // quit
      cout << "Goodbye!" << endl;
      return 0;
    } else if (input == "HELP"){ // help
      cout << "HELP: returns a list of commands (you knew that!)" << endl;
      cout << "QUIT: quits the program" << endl;
      cout << "LOAD: loads integers from a (plaintext) file" << endl;
    } else if (input == "LOAD"){ // load
      cout << "Enter the filename (max 80 chars): " << flush;
      string input;
      cin >> input;
      ifstream file(input);
      char file_text[401]; // QUICK MATH says that 400 should be above the max length of such a file
      file.getline(file_text); // file_text should now have file's data

    }
  }
}
