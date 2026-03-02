// https://github.com/TRVRNB/CppHeap.git
// this is a heap binary tree, a simple data structure that might end up being surprisingly complicated to implement
#include <iostream>
#include <fstream>
#include <cmath> // for round()
#include <string> // first time using std::string, also for stoi()
// apparently i might not actually need nodes for this
// one major problem with this data structure i can think of off the top of my head, is that it doesn't handle collisions very well, especially near the bottom of the tree.
// UPDATE February 27: this is deceptively hard, and i am adding way more comments than I usually do, since there is no way i would understand this code after i make it

using namespace std;


namespace heap_data {
  // i like to use a main namespace to share some variables between functions
  const char version[10] = "1.10";
  const unsigned int array_size = 100;
  unsigned int tree_size = 0; // okay, i'm confused by something. the assignment says "up to 100 numbers will be stored", but also mentions changing the tree size? but what would that even do, if it's just going to parse the same array no matter how many numbers there are? i'll still store it, but i can't think of a use for this variable (other than remove all)
  unsigned int tree[101] = {0}; // this is unwrapped, and index 1 will be treated as index 0, since you can't double index 0 to get its children!
  // i could also just add 1 to the index when doing math, and it would have an absolutely negligible effect on both memory and performance, so why am i mentioning this?
};


int add_to_tree(unsigned short num){
  using namespace heap_data;
  // i don't actually know if this follows the rules of the assignment, i can't really wrap my head around it... but it at least works!
  // unlike the previous version (see commits) this actually goes down the tree repeatedly until it finds a valid space
  // (i spent over an hour debugging that earlier today, only to realize i did it wrong, the new function is MUCH smaller!)
  // (so... i could've easily finished this 2 days ago if i was smarter)
  // 1: success
  // -1: no space
  unsigned int index = 1;
  while (index <= array_size && tree[index] != 0){
    index++;
  }
  if (index > array_size){ // no space left, sorry!
    return -1;
  }
  tree[index] = num;
  // keep swapping until parent is larger
  while (index > 1){ // keep going until at root, at root = ok!
   int parent_index = floor(index / 2);
   if (tree[parent_index] < tree[index]){ // parent is bigger
     unsigned short parent_num = tree[parent_index];
     tree[parent_index] = tree[index];
     tree[index] = parent_num;
     index = parent_index; // move up the ladder!
   } else {
     tree_size += 1;
     return 1;
   }
  }
  tree_size += 1;
  return 1;
}

bool is_digit2(char c){
  // en.cppreference.com/w/cpp/string/byte/isdigit.html
  // this is just a more convenient std::isdigit, since it works with regular chars
  // and returns a bool instead of an int
  return isdigit(static_cast<unsigned char>(c));
}

void add_to_print_heap(short heap_index, short index, short recursion, string* ordered_heap){
  using namespace heap_data;
  // recursive function, adds to the printed version of the heap and then tries to add children
  if (heap_index > array_size){
    return;
  }
  int num = tree[heap_index];
  if (num == 0){
    return;
  }
  string new_string = to_string(recursion) + ") ";
  new_string.append(recursion, '\t');
  new_string += to_string(num);
  ordered_heap[index] = new_string;
  unsigned short child_distance = 32 / pow(2, recursion);
  // now try to add children!
  add_to_print_heap(heap_index * 2 + 1, index + child_distance, recursion + 1, ordered_heap);
  add_to_print_heap(heap_index * 2, index - child_distance, recursion + 1, ordered_heap);
}

void print_heap(){
  using namespace heap_data;
  // print it out
  // the trunk will be in the center, with its branches being 32 spaces away, then 16, then 8, etc.
  // i think it will be best to turn this into an array of strings, which will then be compiled into one big string, which will be printed out
  string* ordered_heap = new string[127];
  // 100 is actually a bad size for this; since the next branch is always twice as big as the previous branch, the amount of slots can be represented by 2^n - 1, where n is the amount of branches (including root)
  // 127 is better since it perfectly fits 7 branches, even though there aren't 7 complete branches. extraneous data will be wiped off anyway!
  // basically, this is just binary, or at least what i remember from a few years ago
  add_to_print_heap(1, 64, 0, ordered_heap);
  string heap_string = "";
  for (int i = 0; i < 127; i++){
    if (ordered_heap[i] != ""){
      heap_string += ordered_heap[i];
      heap_string.append(1, '\n');
    }
  }
  cout << heap_string << endl;
  delete[] ordered_heap; // no need for this anymore
}

void remove_root(){
  using namespace heap_data;
  // remove the root
  // swap it with the bottom-right number, then repeatedly move it up until it is bigger than both children
  cout << tree[1] << endl;
  // look for bottom right leaf
  int index = array_size;
  while (tree[index] == 0 && index != 0){
    index--;
  }
  if (index == 0){
    return; // the heap is empty
  }
  unsigned int num = tree[index];
  tree[1] = num;
  tree[index] = 0;
  tree_size -= 1;
  // now, repeatedly swap it with the larger child until the parent condition is satisfied
  index = 1;
  int old_index;
  bool run_loop = true;
  while (run_loop){
    int child1 = index * 2;
    int child2 = index * 2 + 1;
    if (child2 > array_size){ // out of bounds?
      tree[index] = num;
      run_loop = false;
    } else { // still in bounds
      old_index = index;
      if (tree[child1] > num || tree[child2] > num){
        if (tree[child1] > tree[child2]){
          index = child1;
        } else {
          index = child2;
        }
      tree[old_index] = tree[index]; // swap (part 1)
      } else { // this spot works!
        tree[index] = num; // swap (part 2)
        run_loop = false;
      }
    }
  }
}


int main(){
  using namespace heap_data;
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
      cout << "ADD: add numbers manually" << endl;
      cout << "REMOVE: delete the root from the heap" << endl;
      cout << "REMOVEALL: delete everything, from root, repeatedly" << endl;
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
          if (is_digit2(input1[0])){
            int input_int = stoi(input1); // this might be the best function ever made, finally being able to cast this way after so long in C++ is like finally being able to breathe through my nostrils after i got the flu two weeks ago
            if (0 < input_int && input_int <= 1000){
              int add_result = add_to_tree(input_int);
              if (add_result == 1){
                cout << "Added num " << input_int << endl;
              } else if (add_result == -1){
                cout << "Out of space!" << endl;
              }
            }
          }
        }
      }
      // end of loop
    } else if (input == "PRINT"){ // PRINT
      print_heap();
    } else if (input == "REMOVE"){ // REMOVE
      remove_root();
    } else if (input == "REMOVEALL"){ // REMOVEALL
      unsigned short old_tree_size = tree_size;
      for (int i = 0; i < old_tree_size; i++){
        remove_root();
      };
    }
  }
}
