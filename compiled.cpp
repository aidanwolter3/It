//Aidan Wolter
//Allows program to rewrite themselves

#include <iostream>
using namespace std;

//create the program from the string then tack on the program string at the end
extern string replicator_str;
void rewrite_program(string str);
void rewrite_program(string str) {

  //PROGRAM compile

  //change all the " to \"
  //change all the \ to \\ .
  string actual_str = string(str);
  size_t index_quote = 0;
  size_t index_slash = 0;
  index_quote = actual_str.find("\"", 0);
  index_slash = actual_str.find("\\", 0);
  while((index_quote != string::npos) || (index_slash != string::npos)) {
    if(index_quote < index_slash) {
      actual_str.replace(index_quote, 1, "\\\"");
      index_slash = actual_str.find("\\", index_quote+2);
      index_quote = actual_str.find("\"", index_quote+2);
    }
    else {
      actual_str.replace(index_slash, 1, "\\\\\\\\");
      index_quote = actual_str.find("\"", index_slash+4);
      index_slash = actual_str.find("\\", index_slash+4);
    }
  }

  string str_full;
  str_full += actual_str + "\n";
  str_full += "string program_str = \\\"\\\"\n";

  //for all strings to a newline
  size_t index = 0;
  size_t last_index = 0;
  index = str.find("\n", index);
  while(index != string::npos) {

    //change all the " to \\\"
    //change all the \ to \\\\ .
    string line = str.substr(last_index, index-last_index);
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

    str_full += "\\\"" + line + "\\\\\\\\n\\\"\n";
    index++;
    last_index = index;
    index = str.find("\n", index);
  }
  str_full += ";\n";

  //REPLICATOR compile

  //change all the " to \"
  //change all the \ to \\ .
  string replicator_actual_str = string(replicator_str);
  index_quote = 0;
  index_slash = 0;
  index_quote = replicator_actual_str.find("\"", 0);
  index_slash = replicator_actual_str.find("\\", 0);
  while((index_quote != string::npos) || (index_slash != string::npos)) {
    if(index_quote < index_slash) {
      replicator_actual_str.replace(index_quote, 1, "\\\"");
      index_slash = replicator_actual_str.find("\\", index_quote+2);
      index_quote = replicator_actual_str.find("\"", index_quote+2);
    }
    else {
      replicator_actual_str.replace(index_slash, 1, "\\\\\\\\");
      index_quote = replicator_actual_str.find("\"", index_slash+4);
      index_slash = replicator_actual_str.find("\\", index_slash+4);
    }
  }

  str_full += replicator_actual_str + "\n";
  str_full += "string replicator_str = \\\"\\\"\n";

  //for all strings to a newline
  index = 0;
  last_index = 0;
  index = replicator_str.find("\n", index);
  while(index != string::npos) {

    //change all the " to \\\"
    //change all the \ to \\\\ .
    string line = replicator_str.substr(last_index, index-last_index);
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

    str_full += "\\\"" + line + "\\\\\\\\n\\\"\n";
    index++;
    last_index = index;
    index = replicator_str.find("\n", index);
  }
  str_full += ";";

  //COMPILE and rewrite the program

  //create the echo command to pipe into gcc
  string echo_command = "echo \"" + str_full + "\"";

  //create the entire command for compiling
  string compile_command = echo_command + " | g++-4.9 -o it -xc++ -std=c++11 -";

  //compile the program and replace
  system(compile_command.c_str());
}

string replicator_str = ""
"//Aidan Wolter\n"
"//Allows program to rewrite themselves\n"
"\n"
"#include <iostream>\n"
"using namespace std;\n"
"\n"
"//create the program from the string then tack on the program string at the end\n"
"extern string replicator_str;\n"
"void rewrite_program(string str);\n"
"void rewrite_program(string str) {\n"
"\n"
"  //PROGRAM compile\n"
"\n"
"  //change all the \" to \\\"\n"
"  //change all the \\ to \\\\ .\n"
"  string actual_str = string(str);\n"
"  size_t index_quote = 0;\n"
"  size_t index_slash = 0;\n"
"  index_quote = actual_str.find(\"\\\"\", 0);\n"
"  index_slash = actual_str.find(\"\\\\\", 0);\n"
"  while((index_quote != string::npos) || (index_slash != string::npos)) {\n"
"    if(index_quote < index_slash) {\n"
"      actual_str.replace(index_quote, 1, \"\\\\\\\"\");\n"
"      index_slash = actual_str.find(\"\\\\\", index_quote+2);\n"
"      index_quote = actual_str.find(\"\\\"\", index_quote+2);\n"
"    }\n"
"    else {\n"
"      actual_str.replace(index_slash, 1, \"\\\\\\\\\\\\\\\\\");\n"
"      index_quote = actual_str.find(\"\\\"\", index_slash+4);\n"
"      index_slash = actual_str.find(\"\\\\\", index_slash+4);\n"
"    }\n"
"  }\n"
"\n"
"  string str_full;\n"
"  str_full += actual_str + \"\\n\";\n"
"  str_full += \"string program_str = \\\\\\\"\\\\\\\"\\n\";\n"
"\n"
"  //for all strings to a newline\n"
"  size_t index = 0;\n"
"  size_t last_index = 0;\n"
"  index = str.find(\"\\n\", index);\n"
"  while(index != string::npos) {\n"
"\n"
"    //change all the \" to \\\\\\\"\n"
"    //change all the \\ to \\\\\\\\ .\n"
"    string line = str.substr(last_index, index-last_index);\n"
"    index_quote = 0;\n"
"    index_slash = 0;\n"
"    index_quote = line.find(\"\\\"\", 0);\n"
"    index_slash = line.find(\"\\\\\", 0);\n"
"    while((index_quote != string::npos) || (index_slash != string::npos)) {\n"
"      if(index_quote < index_slash) {\n"
"        line.replace(index_quote, 1, \"\\\\\\\\\\\\\\\"\");\n"
"        index_slash = line.find(\"\\\\\", index_quote+4);\n"
"        index_quote = line.find(\"\\\"\", index_quote+4);\n"
"      }\n"
"      else {\n"
"        line.replace(index_slash, 1, \"\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\");\n"
"        index_quote = line.find(\"\\\"\", index_slash+8);\n"
"        index_slash = line.find(\"\\\\\", index_slash+8);\n"
"      }\n"
"    }\n"
"\n"
"    str_full += \"\\\\\\\"\" + line + \"\\\\\\\\\\\\\\\\n\\\\\\\"\\n\";\n"
"    index++;\n"
"    last_index = index;\n"
"    index = str.find(\"\\n\", index);\n"
"  }\n"
"  str_full += \";\\n\";\n"
"\n"
"  //REPLICATOR compile\n"
"\n"
"  //change all the \" to \\\"\n"
"  //change all the \\ to \\\\ .\n"
"  string replicator_actual_str = string(replicator_str);\n"
"  index_quote = 0;\n"
"  index_slash = 0;\n"
"  index_quote = replicator_actual_str.find(\"\\\"\", 0);\n"
"  index_slash = replicator_actual_str.find(\"\\\\\", 0);\n"
"  while((index_quote != string::npos) || (index_slash != string::npos)) {\n"
"    if(index_quote < index_slash) {\n"
"      replicator_actual_str.replace(index_quote, 1, \"\\\\\\\"\");\n"
"      index_slash = replicator_actual_str.find(\"\\\\\", index_quote+2);\n"
"      index_quote = replicator_actual_str.find(\"\\\"\", index_quote+2);\n"
"    }\n"
"    else {\n"
"      replicator_actual_str.replace(index_slash, 1, \"\\\\\\\\\\\\\\\\\");\n"
"      index_quote = replicator_actual_str.find(\"\\\"\", index_slash+4);\n"
"      index_slash = replicator_actual_str.find(\"\\\\\", index_slash+4);\n"
"    }\n"
"  }\n"
"\n"
"  str_full += replicator_actual_str + \"\\n\";\n"
"  str_full += \"string replicator_str = \\\\\\\"\\\\\\\"\\n\";\n"
"\n"
"  //for all strings to a newline\n"
"  index = 0;\n"
"  last_index = 0;\n"
"  index = replicator_str.find(\"\\n\", index);\n"
"  while(index != string::npos) {\n"
"\n"
"    //change all the \" to \\\\\\\"\n"
"    //change all the \\ to \\\\\\\\ .\n"
"    string line = replicator_str.substr(last_index, index-last_index);\n"
"    index_quote = 0;\n"
"    index_slash = 0;\n"
"    index_quote = line.find(\"\\\"\", 0);\n"
"    index_slash = line.find(\"\\\\\", 0);\n"
"    while((index_quote != string::npos) || (index_slash != string::npos)) {\n"
"      if(index_quote < index_slash) {\n"
"        line.replace(index_quote, 1, \"\\\\\\\\\\\\\\\"\");\n"
"        index_slash = line.find(\"\\\\\", index_quote+4);\n"
"        index_quote = line.find(\"\\\"\", index_quote+4);\n"
"      }\n"
"      else {\n"
"        line.replace(index_slash, 1, \"\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\");\n"
"        index_quote = line.find(\"\\\"\", index_slash+8);\n"
"        index_slash = line.find(\"\\\\\", index_slash+8);\n"
"      }\n"
"    }\n"
"\n"
"    str_full += \"\\\\\\\"\" + line + \"\\\\\\\\\\\\\\\\n\\\\\\\"\\n\";\n"
"    index++;\n"
"    last_index = index;\n"
"    index = replicator_str.find(\"\\n\", index);\n"
"  }\n"
"  str_full += \";\";\n"
"\n"
"  //COMPILE and rewrite the program\n"
"\n"
"  //create the echo command to pipe into gcc\n"
"  string echo_command = \"echo \\\"\" + str_full + \"\\\"\";\n"
"\n"
"  //create the entire command for compiling\n"
"  string compile_command = echo_command + \" | g++-4.9 -o it -xc++ -std=c++11 -\";\n"
"\n"
"  //compile the program and replace\n"
"  system(compile_command.c_str());\n"
"}\n"
"\n"
;
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

string program_str = ""
"#include <iostream>\n"
"\n"
"using namespace std;\n"
"\n"
"void rewrite_program(string str);\n"
"extern string program_str;\n"
"\n"
"int val = 0;\n"
"int main(int argc, char *argv[]) {\n"
"\n"
"  //output the current value and prompt for the new value\n"
"  cout << val << endl;\n"
"  cout << \"enter a new value: \";\n"
"  cin >> val;\n"
"  string new_val_str = \"int val = \" + to_string(val) + \";\\n\";\n"
"\n"
"  //replace the 10th line\n"
"  size_t line_start = 0;\n"
"  size_t line_end = 0;\n"
"  int line_to_edit = 9;\n"
"  for(int i = 0; i < line_to_edit; i++) {\n"
"    line_start = program_str.find(\"\\n\", line_start);\n"
"    line_start++;\n"
"  }\n"
"  line_end = program_str.find(\"\\n\", line_start);\n"
"  program_str.replace(line_start, line_end-line_start, new_val_str);\n"
"\n"
"  rewrite_program(program_str);\n"
"  return 0;\n"
"}\n"
"\n"
;
