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
#include <sstream>
#include <vector>
#include <curses.h>

using namespace std;

void rewrite_program(string str);
extern string program_str;

static void finish(int sig);

typedef enum it_mode_t{
  mode_base,
  mode_insert
} it_mode_t;

//int val = 0;
int main(int argc, char *argv[]) {
  int num = 0;

  //create interrupt ^C to break
  signal(SIGINT, finish);

  //initialize library
  initscr();

  //enable keyboard mapping
  keypad(stdscr, TRUE);

  //do not convert \n to \r\n
  nonl();

  //take input one character at a time and do not wait for \n
  cbreak();

  //disable automatic echo
  noecho();

  idlok(stdscr, TRUE);
  scrollok(stdscr, TRUE);

  //keep track of the current mode
  it_mode_t mode = mode_base;

  //keep track of the current position within the file
  int cur_file_posx = 0;
  int cur_file_posy = 0;

  //keep track of the window size and the cursor position
  int winx, winy;
  int curx, cury;
  getmaxyx(stdscr, winy, winx);

  //get the lines from the program string
  vector<string> lines;
  istringstream program_str_stream(program_str);
  string line;
  while(getline(program_str_stream, line)) {
    lines.push_back(line);
  }

  //print the screen with the program string
  for(int i = 0; i < winy; i++) {
    move(i, 0);
    if(i > lines.size()-1) {
      break;
    }
    addstr(lines[i].c_str());
  }
  move(0, 0);

  //infinitely loop over getting input
  for(;;) {
    getyx(stdscr, cury, curx);
    getmaxyx(stdscr, winy, winx);

    switch(mode) {
      case mode_base: {
        int c = getch();

        //enter insert mode
        if(c == 'i') {
          mode = mode_insert;
        }

        //move the cursor around with hjkl
        else if(c == 'h' || c == 'j' || c == 'k' || c == 'l') {
          if(c == 'h') {
            if(curx > 0) {
              cur_file_posx--;
              curx--;
            }
          }
          else if(c == 'j') {
            if(cury < winy-1) {
              cur_file_posy++;
              cury++;
            }
            else if(cur_file_posy < lines.size()) {
              scroll(stdscr);
              cur_file_posy++;
              move(cury, 0);
              addstr(lines[cur_file_posy].c_str());
            }
          }
          else if(c == 'k') {
            if(cury > 0) {
              cur_file_posy--;
              cury--;
            }
            else if(cur_file_posy > 0) {
              scrl(-1);
              cur_file_posy--;
              addstr(lines[cur_file_posy].c_str());
            }
          }
          else if(c == 'l') {
            if(curx < winx) {
              cur_file_posx++;
              curx++;
            }
          }
          move(cury, curx);
        }

        break;
      }

      case mode_insert: {
        int c = getch();

        //go back to base mode
        if(c == 27) {
          mode = mode_base;
          continue;
        }

        addch(c);

        break;
      }
    }
  }

  finish(0);

  //output the current value and prompt for the new value
  //cout << val << endl;
  //cout << "enter a new value: ";
  //cin >> val;
  //string new_val_str = "int val = " + to_string(val) + ";\n";

  ////replace the 10th line
  //size_t line_start = 0;
  //size_t line_end = 0;
  //int line_to_edit = 9;
  //for(int i = 0; i < line_to_edit; i++) {
  //  line_start = program_str.find("\n", line_start);
  //  line_start++;
  //}
  //line_end = program_str.find("\n", line_start);
  //program_str.replace(line_start, line_end-line_start, new_val_str);

  //rewrite_program(program_str);
  //return 0;
}

static void finish(int sig) {
  endwin();
  exit(0);
}
string program_str = ""
"#include <iostream>\n"
"#include <sstream>\n"
"#include <vector>\n"
"#include <curses.h>\n"
"\n"
"using namespace std;\n"
"\n"
"void rewrite_program(string str);\n"
"extern string program_str;\n"
"\n"
"static void finish(int sig);\n"
"\n"
"typedef enum it_mode_t{\n"
"  mode_base,\n"
"  mode_insert\n"
"} it_mode_t;\n"
"\n"
"//int val = 0;\n"
"int main(int argc, char *argv[]) {\n"
"  int num = 0;\n"
"\n"
"  //create interrupt ^C to break\n"
"  signal(SIGINT, finish);\n"
"\n"
"  //initialize library\n"
"  initscr();\n"
"\n"
"  //enable keyboard mapping\n"
"  keypad(stdscr, TRUE);\n"
"\n"
"  //do not convert \\n to \\r\\n\n"
"  nonl();\n"
"\n"
"  //take input one character at a time and do not wait for \\n\n"
"  cbreak();\n"
"\n"
"  //disable automatic echo\n"
"  noecho();\n"
"\n"
"  idlok(stdscr, TRUE);\n"
"  scrollok(stdscr, TRUE);\n"
"\n"
"  //keep track of the current mode\n"
"  it_mode_t mode = mode_base;\n"
"\n"
"  //keep track of the current position within the file\n"
"  int cur_file_posx = 0;\n"
"  int cur_file_posy = 0;\n"
"\n"
"  //keep track of the window size and the cursor position\n"
"  int winx, winy;\n"
"  int curx, cury;\n"
"  getmaxyx(stdscr, winy, winx);\n"
"\n"
"  //get the lines from the program string\n"
"  vector<string> lines;\n"
"  istringstream program_str_stream(program_str);\n"
"  string line;\n"
"  while(getline(program_str_stream, line)) {\n"
"    lines.push_back(line);\n"
"  }\n"
"\n"
"  //print the screen with the program string\n"
"  for(int i = 0; i < winy; i++) {\n"
"    move(i, 0);\n"
"    if(i > lines.size()-1) {\n"
"      break;\n"
"    }\n"
"    addstr(lines[i].c_str());\n"
"  }\n"
"  move(0, 0);\n"
"\n"
"  //infinitely loop over getting input\n"
"  for(;;) {\n"
"    getyx(stdscr, cury, curx);\n"
"    getmaxyx(stdscr, winy, winx);\n"
"\n"
"    switch(mode) {\n"
"      case mode_base: {\n"
"        int c = getch();\n"
"\n"
"        //enter insert mode\n"
"        if(c == 'i') {\n"
"          mode = mode_insert;\n"
"        }\n"
"\n"
"        //move the cursor around with hjkl\n"
"        else if(c == 'h' || c == 'j' || c == 'k' || c == 'l') {\n"
"          if(c == 'h') {\n"
"            if(curx > 0) {\n"
"              cur_file_posx--;\n"
"              curx--;\n"
"            }\n"
"          }\n"
"          else if(c == 'j') {\n"
"            if(cury < winy-1) {\n"
"              cur_file_posy++;\n"
"              cury++;\n"
"            }\n"
"            else if(cur_file_posy < lines.size()) {\n"
"              scroll(stdscr);\n"
"              cur_file_posy++;\n"
"              move(cury, 0);\n"
"              addstr(lines[cur_file_posy].c_str());\n"
"            }\n"
"          }\n"
"          else if(c == 'k') {\n"
"            if(cury > 0) {\n"
"              cur_file_posy--;\n"
"              cury--;\n"
"            }\n"
"            else if(cur_file_posy > 0) {\n"
"              scrl(-1);\n"
"              cur_file_posy--;\n"
"              addstr(lines[cur_file_posy].c_str());\n"
"            }\n"
"          }\n"
"          else if(c == 'l') {\n"
"            if(curx < winx) {\n"
"              cur_file_posx++;\n"
"              curx++;\n"
"            }\n"
"          }\n"
"          move(cury, curx);\n"
"        }\n"
"\n"
"        break;\n"
"      }\n"
"\n"
"      case mode_insert: {\n"
"        int c = getch();\n"
"\n"
"        //go back to base mode\n"
"        if(c == 27) {\n"
"          mode = mode_base;\n"
"          continue;\n"
"        }\n"
"\n"
"        addch(c);\n"
"\n"
"        break;\n"
"      }\n"
"    }\n"
"  }\n"
"\n"
"  finish(0);\n"
"\n"
"  //output the current value and prompt for the new value\n"
"  //cout << val << endl;\n"
"  //cout << \"enter a new value: \";\n"
"  //cin >> val;\n"
"  //string new_val_str = \"int val = \" + to_string(val) + \";\\n\";\n"
"\n"
"  ////replace the 10th line\n"
"  //size_t line_start = 0;\n"
"  //size_t line_end = 0;\n"
"  //int line_to_edit = 9;\n"
"  //for(int i = 0; i < line_to_edit; i++) {\n"
"  //  line_start = program_str.find(\"\\n\", line_start);\n"
"  //  line_start++;\n"
"  //}\n"
"  //line_end = program_str.find(\"\\n\", line_start);\n"
"  //program_str.replace(line_start, line_end-line_start, new_val_str);\n"
"\n"
"  //rewrite_program(program_str);\n"
"  //return 0;\n"
"}\n"
"\n"
"static void finish(int sig) {\n"
"  endwin();\n"
"  exit(0);\n"
"}\n"
;
