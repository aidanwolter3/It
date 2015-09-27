#include <iostream>

using namespace std;

void rewrite_program(string str);
extern string program_str;

int val = 0;
int main(int argc, char *argv[]) {

  //output the current value and prompt for the new value
  cout << val << endl;
  cout << "enter a new value: ";
  cin >> val;
  string new_val_str = "int val = " + to_string(val) + ";\n";

  //replace the 10th line
  size_t line_start = 0;
  size_t line_end = 0;
  int line_to_edit = 9;
  for(int i = 0; i < line_to_edit; i++) {
    line_start = program_str.find("\n", line_start);
    line_start++;
  }
  line_end = program_str.find("\n", line_start);
  program_str.replace(line_start, line_end-line_start, new_val_str);

  rewrite_program(program_str);
  return 0;
}

