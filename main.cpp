// https://github.com/TRVRNB/CppHeap.git
// this is a heap binary tree, a simple data structure that might end up being surprisingly complicated to implement
#include <iostream>
#include <fstream>
#include <cmath> // for round()
#include <cstring> // for numerous functions (useless comment, i know)
#include <string> // first time using std::string, also for stoi()
// apparently i might not actually need nodes for this
// one major problem with this data structure i can think of off the top of my head, is that it doesn't handle collisions very well, especially near the bottom of the tree.
// UPDATE February 27: this is deceptively hard, and i am adding way more comments than I usually do, since there is no way i would understand this code after i make it

using namespace std;


namespace heap_data {
  // i like to use a main namespace to share some variables between functions
  const char version[10] = "1.6";
  const unsigned int tree_size = 100;
  unsigned int tree[101] = {0}; // this is unwrapped, and index 1 will be treated as index 0, since you can't double index 0 to get its children!
  // i could also just add 1 to the index when doing math, and it would have an absolutely negligible effect on both memory and performance, so why am i mentioning this?
};
using namespace heap_data;


int add_to_next(int index, unsigned int num){
  // this is recursive, and will repeatedly go down the tree until it finds space
  // 1: success
  // -1: no space
  // -2: etc.
  if (index > tree_size){
    return -1;
  }
  if (index != 1){ // anything BUT root
    unsigned int parent_index = floor(index / 2);
    if (tree[parent_index] < num){ // parent is smaller, not allowed
      return -2; // since there's no resizing... oh well? you could look through another chain instead
    }
  }
  // from now on, assume the parent EXISTS and is VALID
  if (tree[index] == 0){ // is empty
    tree[index] = num;
    return 1; // success!
  }
  // from now on, assume the current slot isn't valid, so needd to look for a new one
  int child_index = index * 2 + 1; // start on child 2
  if (child_index <= tree_size){
    int adding_result = add_to_next(child_index, num);
    if (adding_result != -1){
      return adding_result;
    }
  }
  child_index -= 1;
  if (child_index <= tree_size){
    return add_to_next(child_index, num);
  }
  return -1; // no space in this chain!
}

bool is_digit2(char c){
  // en.cppreference.com/w/cppp/string/byte/isdigit.html
  // this is just a more convenient std::isdigit, since it works with regular chars
  // and returns a bool instead of an int
  return isdigit(static_cast<unsigned char>(c));
}


int add_to_tree(unsigned int num){
  // look for a valid spot, then add to the tree
  for (int i = 1; i < tree_size + 1; i++){
    if (tree[i] == 0){ // spot found
      return add_to_next(i, num);
    }
  }
  return -1; // this probably means it ran out of space, but there won't be any resizing logic in this progam.
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
      cout << "ADD: add numbers manually";
    } else if (input == "LOAD"){ // load
      cout << "Enter the filename (max 80 chars): " << flush;
      string input;
      cin >> input;
      ifstream file(input);
      char file_text_array[401] = ""; // this should be above the max size
      // now, find out how to get data from file
      file.getline(file_text_array, 401);
      string file_text(file_text_array);
      if (file_text.length() == 0){
	cout << "Error: " << input << " not found in current folder; maybe there's a typo?" << endl;
      } else {
	// i WOULD delete file_text_array here, but i think it will go out of scope soon anyway?
	// have to parse data manually, since i can't find a function to do this for me
	int string_index = 0;
	for (int i = 0; i < 100; i++){
	  if (string_index < file_text.length()){
	    string current_num = "";
	    int j = 0;
	    // individual numbers
	    while ((file_text[string_index] != ' ') && (j < 4)){
	      current_num.append(1, file_text[string_index]); // append this char once
	      string_index += 1;
	      j++;
	  }
	    string_index += 1;
	    int input_int = stoi(current_num);
	    int add_result = add_to_tree(input_int);
	    if (add_result == 1){
	      cout << "Added num " << input_int << endl;
	    } else if (add_result == -1){
	      cout << "Out of space!" << endl;
	    } else {
	      cout << "There was an error; that's all I know." << endl;
	    }
	  }
	  cout << "Done!" << endl;
	}
      }
    } else if (input == "ADD"){ // ADD
      cout << "Type 'QUIT' to stop adding numbers." << endl;
      string input1 = "";
      while (input1 != "QUIT"){ // keep going until they want to stop
	cout << "$ Add this number: " << flush;
	cin >> input1;
	if (input1 != "QUIT"){
	  int input_int = stoi(input1); // this might be the best function ever made, finally being able to cast this way after so long in C++ is like finally being able to breathe through my nostrils after i got the flu two weeks ago
	  int add_result = add_to_tree(input_int);
	  if (add_result == 1){
	    cout << "Added num " << input_int << endl;
	  } else if (add_result == -1){
	    cout << "Out of space!" << endl;
	  } else {
	    cout << "There was an error; that's all I know." << endl;
	  }
	}
      }
      // end of loop
    }
  }
}
