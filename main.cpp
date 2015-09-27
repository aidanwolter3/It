#include <iostream>

using namespace std;

extern string program_str;
extern int val;
void write_program_string(string program_str);
string build_program_string(string program_str, int val);

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

  string program_str_full;
  program_str_full = build_program_string(program_str, val);
  write_program_string(program_str_full);
  return 0;
}

//compile and overwrite the it text editor
void write_program_string(string program_str) {
  
  //create the echo command to pipe into gcc
  string echo_command = "echo \"" + program_str + "\"";

  //create the entire command for compiling
  string compile_command = echo_command + " | g++-4.9 -o it -xc++ -std=c++11 -";

  //compile the program and replace
  system(compile_command.c_str());
}

//create the program from the string then tack on the program string at the end
string build_program_string(string program_str, int val) {

  //change all the " to \"
  //change all the \ to \\ .
  string actual_program_str = string(program_str);
  size_t index_quote = 0;
  size_t index_slash = 0;
  index_quote = actual_program_str.find("\"", 0);
  index_slash = actual_program_str.find("\\", 0);
  while((index_quote != string::npos) || (index_slash != string::npos)) {
    if(index_quote < index_slash) {
      actual_program_str.replace(index_quote, 1, "\\\"");
      index_slash = actual_program_str.find("\\", index_quote+2);
      index_quote = actual_program_str.find("\"", index_quote+2);
    }
    else {
      actual_program_str.replace(index_slash, 1, "\\\\\\\\");
      index_quote = actual_program_str.find("\"", index_slash+4);
      index_slash = actual_program_str.find("\\", index_slash+4);
    }
  }

  string program_str_full;
  program_str_full += actual_program_str + "\n";
  program_str_full += "string program_str = \\\"\\\"\n";

  //for all strings to a newline
  size_t index = 0;
  size_t last_index = 0;
  index = program_str.find("\n", index);
  while(index != string::npos) {

    //change all the " to \\\"
    //change all the \ to \\\\ .
    string line = program_str.substr(last_index, index-last_index);
    index_quote = 0;
    index_slash = 0;
    index_quote = line.find("\"", 0);
    index_slash = line.find("\\", 0);
    while((index_quote != string::npos) || (index_slash != string::npos)) {
      if(index_quote < index_slash) {
        line.replace(index_quote, 1, "\\\\\\\"");
        index_slash = line.find("\\", index_quote+4);
        index_quote = line.find("\"", index_quote+4);
      }
      else {
        line.replace(index_slash, 1, "\\\\\\\\\\\\\\\\");
        index_quote = line.find("\"", index_slash+8);
        index_slash = line.find("\\", index_slash+8);
      }
    }

    program_str_full += "\\\"" + line + "\\\\\\\\n\\\"\n";
    index++;
    last_index = index;
    index = program_str.find("\n", index);
  }
  program_str_full += ";";
  return program_str_full;
}

