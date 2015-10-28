//Aidan Wolter
//Allows program to rewrite themselves

#include <iostream>
#include <vector>

using namespace std;

//create the program from the string then tack on the program string at the end
extern string replicator_str;
void rewrite_program(string str, vector<string> *lines);
void rewrite_program(string str, vector<string> *lines) {

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
  string compile_command = echo_command + " | g++-4.9 -o it -xc++ -lncurses -std=c++11 - 2>&1";

  //compile the program and replace
  FILE *output = popen(compile_command.c_str(), "r");
  lines->clear();

  char cline[1024];
  while(fgets(cline, 1024, output)) {
    string line = cline;
    lines->push_back(line);
  }

  return;
}

