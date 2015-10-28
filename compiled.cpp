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

string replicator_str = ""
"//Aidan Wolter\n"
"//Allows program to rewrite themselves\n"
"\n"
"#include <iostream>\n"
"#include <vector>\n"
"\n"
"using namespace std;\n"
"\n"
"//create the program from the string then tack on the program string at the end\n"
"extern string replicator_str;\n"
"void rewrite_program(string str, vector<string> *lines);\n"
"void rewrite_program(string str, vector<string> *lines) {\n"
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
"  string compile_command = echo_command + \" | g++-4.9 -o it -xc++ -lncurses -std=c++11 - 2>&1\";\n"
"\n"
"  //compile the program and replace\n"
"  FILE *output = popen(compile_command.c_str(), \"r\");\n"
"  lines->clear();\n"
"\n"
"  char cline[1024];\n"
"  while(fgets(cline, 1024, output)) {\n"
"    string line = cline;\n"
"    lines->push_back(line);\n"
"  }\n"
"\n"
"  return;\n"
"}\n"
"\n"
;
#include <iostream>
#include <sstream>
#include <vector>
#include <curses.h>

using namespace std;

#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))

void rewrite_program(string str);
void rewrite_buffer();
extern string program_str;

static void finish(int sig);

typedef enum it_mode_t{
  mode_base,
  mode_insert
} it_mode_t;

typedef enum it_buffer_t{
  it_buffer_program,
  it_buffer_compile_output
} it_buffer_t;

vector<string> buffer_lines;
vector<string> compile_output;
vector<string> program_lines;

//keep track of the window size and the cursor position
int winx, winy;
int curx, cury;

//keep track of the current position within the file
int cur_file_posx = 0;
int cur_file_posy = 0;

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

  getmaxyx(stdscr, winy, winx);
  winy -= 2;

  //get the buffer_lines from the program string
  istringstream program_str_stream(program_str);
  string line;
  while(getline(program_str_stream, line)) {
    program_lines.push_back(line);
  }
  buffer_lines.insert(buffer_lines.begin(), program_lines.begin(), program_lines.end());

  //print the screen with the program string
  for(int i = 0; i < winy; i++) {
    move(i, 0);
    if(i > buffer_lines.size()-1) {
      break;
    }
    addstr(buffer_lines[i].c_str());
  }
  move(0, 0);

  //infinitely loop over getting input
  int buffer_contents = it_buffer_program;
  for(;;) {
    getyx(stdscr, cury, curx);
    getmaxyx(stdscr, winy, winx);
    winy -= 2;

    switch(mode) {
      case mode_base: {
        int c = getch();

        //enter insert mode
        if(c == 'i') {
          if(buffer_contents == it_buffer_program) {
            mode = mode_insert;
          }
        }

        //quit
        else if(c == 'q') {
          finish(0);
        }

        //rewrite the program
        else if(c == 'w') {

          //save the buffer into the lines of the program
          program_lines.clear();
          program_lines.insert(program_lines.begin(), buffer_lines.begin(), buffer_lines.end());

          //recreate the program string
          program_str = "";
          for(auto line : program_lines) {
            program_str += line + '\n';
          }

          rewrite_program(program_str, &compile_output);

          //determine and show the result
          if(compile_output.size() > 0) {
            move(winy+1, 0);
            addstr("REWRITE ERROR: type 'o' in command mode to see the output");
            move(cury, curx);
          }
          else {
            move(winy+1, 0);
            addstr("REWRITE SUCCESS");
            move(cury, curx);
          }
        }

        //show compile output
        else if(c == 'o') {
          buffer_lines.clear();

          if(buffer_contents == it_buffer_program) {
            buffer_lines.insert(buffer_lines.begin(), compile_output.begin(), compile_output.end());
            buffer_contents = it_buffer_compile_output;
          }
          else if(buffer_contents == it_buffer_compile_output) {
            buffer_lines.insert(buffer_lines.begin(), program_lines.begin(), program_lines.end());
            buffer_contents = it_buffer_program;
          }

          rewrite_buffer();
        }

        //move the cursor around with hjkl
        else if(c == 'h' || c == 'j' || c == 'k' || c == 'l') {

          //remove any messages
          move(winy+1, 0);
          clrtoeol();

          if(c == 'h') {
            if(cur_file_posx > 0) {
              cur_file_posx = curx-1;
              curx = cur_file_posx;
            }
          }
          else if(c == 'j') {
            if(cury < min(winy-2, buffer_lines.size())) {
              cur_file_posy++;
              cury++;
            }
            else if(cur_file_posy < buffer_lines.size()-1) {
              scroll(stdscr);
              cur_file_posy++;
              move(cury, 0);
              addstr(buffer_lines[cur_file_posy].c_str());
            }

            //ensure we are placed correctly on the x axis
            curx = cur_file_posx;
          }
          else if(c == 'k') {
            if(cury > 0) {
              cur_file_posy--;
              cury--;
            }
            else if(cur_file_posy > 0) {
              scrl(-1);
              cur_file_posy--;
              move(cury, 0);
              addstr(buffer_lines[cur_file_posy].c_str());
            }

            //ensure we are placed correctly on the x axis
            curx = cur_file_posx;
          }
          else if(c == 'l') {
            if(curx < winx) {
              cur_file_posx = curx+1;
              curx = cur_file_posx;
            }
          }

          //restrict the cursor's x coordinate to the length of the string
          if(curx >= buffer_lines[cur_file_posy].size()) {
            curx = buffer_lines[cur_file_posy].size();
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
        }

        //handle newlines by scrolling up and splitting buffer_lines
        else if(c == '\r') {
          string line_start = buffer_lines[cur_file_posy].substr(0, curx);
          string line_end = buffer_lines[cur_file_posy].substr(curx, buffer_lines[cur_file_posy].size()-curx);

          //rewrite the current line
          buffer_lines[cur_file_posy] = line_start;
          clrtoeol();

          //add the new line
          buffer_lines.insert(buffer_lines.begin()+cur_file_posy+1, line_end);

          //reprint all the buffer_lines after
          for(int i = cur_file_posy+1; i < buffer_lines.size(); i++) {
            if(i >= winy) {
              break;
            }
            move(cury+i-cur_file_posy, 0);
            clrtoeol();
            addstr(buffer_lines[i].c_str());
          }

          //move the cursor down the cursor
          cur_file_posy++;
          cury++;

          //scroll if the cursor passed the screen
          move(cury, 0);
          if(cury >= winy) {
            scroll(stdscr);
            cury = winy-1;
            addstr(buffer_lines[cur_file_posy].c_str());
            move(cury, 0);
          }
        }

        //delete or backspace
        else if(c == 127 || c == 8) {
          if(curx > 0) {
            string line = buffer_lines[cur_file_posy];
            buffer_lines[cur_file_posy] = line.substr(0, curx-1) + line.substr(curx, line.size()-curx);
            cur_file_posx--;
            curx--;
            move(cury, curx);
            delch();
          }
          else if(cur_file_posy > 0) {
            int new_posx = buffer_lines[cur_file_posy-1].size();
            string bigger_line = buffer_lines[cur_file_posy-1] + buffer_lines[cur_file_posy];
            buffer_lines[cur_file_posy-1] = bigger_line;
            buffer_lines.erase(buffer_lines.begin()+cur_file_posy);

            if(cury > 0) {

              //reprint all buffer_lines after
              for(int i = cur_file_posy-1; i < buffer_lines.size(); i++) {
                if(i >= winy) {
                  break;
                }
                move(cury+i-cur_file_posy, 0);
                clrtoeol();
                addstr(buffer_lines[i].c_str());
              }

              //move the cursor
              cur_file_posy--;
              cury--;
              move(cury, new_posx);
              cur_file_posx = new_posx;
            }
            else {
              move(cury, 0);
              clrtoeol();
              addstr(buffer_lines[cur_file_posy].c_str());
              move(cury, new_posx);
              cur_file_posx = new_posx;
            }
          }
        }

        //regular character
        else {

          //add the character to the line
          string line_end = (char)c + buffer_lines[cur_file_posy].substr(curx, buffer_lines[cur_file_posy].size()-curx);
          buffer_lines[cur_file_posy] = buffer_lines[cur_file_posy].substr(0, curx) + line_end;
          move(cury, curx);
          addstr(line_end.c_str());

          curx++;
          cur_file_posx = curx;
          move(cury, curx);
        }

        break;
      }
    }
  }

  finish(0);

  return 0;
}

void rewrite_buffer() {
  clear();
  for(int i = 0; i < buffer_lines.size() && i < winy; i++) {
    move(i, 0);
    addstr(buffer_lines[i].c_str());
  }
  move(0, 0);
  cur_file_posy = 0;
  cur_file_posx = 0;
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
"#define min(a,b) ((a) < (b) ? (a) : (b))\n"
"#define max(a,b) ((a) > (b) ? (a) : (b))\n"
"\n"
"void rewrite_program(string str);\n"
"void rewrite_buffer();\n"
"extern string program_str;\n"
"\n"
"static void finish(int sig);\n"
"\n"
"typedef enum it_mode_t{\n"
"  mode_base,\n"
"  mode_insert\n"
"} it_mode_t;\n"
"\n"
"typedef enum it_buffer_t{\n"
"  it_buffer_program,\n"
"  it_buffer_compile_output\n"
"} it_buffer_t;\n"
"\n"
"vector<string> buffer_lines;\n"
"vector<string> compile_output;\n"
"vector<string> program_lines;\n"
"\n"
"//keep track of the window size and the cursor position\n"
"int winx, winy;\n"
"int curx, cury;\n"
"\n"
"//keep track of the current position within the file\n"
"int cur_file_posx = 0;\n"
"int cur_file_posy = 0;\n"
"\n"
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
"  getmaxyx(stdscr, winy, winx);\n"
"  winy -= 2;\n"
"\n"
"  //get the buffer_lines from the program string\n"
"  istringstream program_str_stream(program_str);\n"
"  string line;\n"
"  while(getline(program_str_stream, line)) {\n"
"    program_lines.push_back(line);\n"
"  }\n"
"  buffer_lines.insert(buffer_lines.begin(), program_lines.begin(), program_lines.end());\n"
"\n"
"  //print the screen with the program string\n"
"  for(int i = 0; i < winy; i++) {\n"
"    move(i, 0);\n"
"    if(i > buffer_lines.size()-1) {\n"
"      break;\n"
"    }\n"
"    addstr(buffer_lines[i].c_str());\n"
"  }\n"
"  move(0, 0);\n"
"\n"
"  //infinitely loop over getting input\n"
"  int buffer_contents = it_buffer_program;\n"
"  for(;;) {\n"
"    getyx(stdscr, cury, curx);\n"
"    getmaxyx(stdscr, winy, winx);\n"
"    winy -= 2;\n"
"\n"
"    switch(mode) {\n"
"      case mode_base: {\n"
"        int c = getch();\n"
"\n"
"        //enter insert mode\n"
"        if(c == 'i') {\n"
"          if(buffer_contents == it_buffer_program) {\n"
"            mode = mode_insert;\n"
"          }\n"
"        }\n"
"\n"
"        //quit\n"
"        else if(c == 'q') {\n"
"          finish(0);\n"
"        }\n"
"\n"
"        //rewrite the program\n"
"        else if(c == 'w') {\n"
"\n"
"          //save the buffer into the lines of the program\n"
"          program_lines.clear();\n"
"          program_lines.insert(program_lines.begin(), buffer_lines.begin(), buffer_lines.end());\n"
"\n"
"          //recreate the program string\n"
"          program_str = \"\";\n"
"          for(auto line : program_lines) {\n"
"            program_str += line + '\\n';\n"
"          }\n"
"\n"
"          rewrite_program(program_str, &compile_output);\n"
"\n"
"          //determine and show the result\n"
"          if(compile_output.size() > 0) {\n"
"            move(winy+1, 0);\n"
"            addstr(\"REWRITE ERROR: type 'o' in command mode to see the output\");\n"
"            move(cury, curx);\n"
"          }\n"
"          else {\n"
"            move(winy+1, 0);\n"
"            addstr(\"REWRITE SUCCESS\");\n"
"            move(cury, curx);\n"
"          }\n"
"        }\n"
"\n"
"        //show compile output\n"
"        else if(c == 'o') {\n"
"          buffer_lines.clear();\n"
"\n"
"          if(buffer_contents == it_buffer_program) {\n"
"            buffer_lines.insert(buffer_lines.begin(), compile_output.begin(), compile_output.end());\n"
"            buffer_contents = it_buffer_compile_output;\n"
"          }\n"
"          else if(buffer_contents == it_buffer_compile_output) {\n"
"            buffer_lines.insert(buffer_lines.begin(), program_lines.begin(), program_lines.end());\n"
"            buffer_contents = it_buffer_program;\n"
"          }\n"
"\n"
"          rewrite_buffer();\n"
"        }\n"
"\n"
"        //move the cursor around with hjkl\n"
"        else if(c == 'h' || c == 'j' || c == 'k' || c == 'l') {\n"
"\n"
"          //remove any messages\n"
"          move(winy+1, 0);\n"
"          clrtoeol();\n"
"\n"
"          if(c == 'h') {\n"
"            if(cur_file_posx > 0) {\n"
"              cur_file_posx = curx-1;\n"
"              curx = cur_file_posx;\n"
"            }\n"
"          }\n"
"          else if(c == 'j') {\n"
"            if(cury < min(winy-2, buffer_lines.size())) {\n"
"              cur_file_posy++;\n"
"              cury++;\n"
"            }\n"
"            else if(cur_file_posy < buffer_lines.size()-1) {\n"
"              scroll(stdscr);\n"
"              cur_file_posy++;\n"
"              move(cury, 0);\n"
"              addstr(buffer_lines[cur_file_posy].c_str());\n"
"            }\n"
"\n"
"            //ensure we are placed correctly on the x axis\n"
"            curx = cur_file_posx;\n"
"          }\n"
"          else if(c == 'k') {\n"
"            if(cury > 0) {\n"
"              cur_file_posy--;\n"
"              cury--;\n"
"            }\n"
"            else if(cur_file_posy > 0) {\n"
"              scrl(-1);\n"
"              cur_file_posy--;\n"
"              move(cury, 0);\n"
"              addstr(buffer_lines[cur_file_posy].c_str());\n"
"            }\n"
"\n"
"            //ensure we are placed correctly on the x axis\n"
"            curx = cur_file_posx;\n"
"          }\n"
"          else if(c == 'l') {\n"
"            if(curx < winx) {\n"
"              cur_file_posx = curx+1;\n"
"              curx = cur_file_posx;\n"
"            }\n"
"          }\n"
"\n"
"          //restrict the cursor's x coordinate to the length of the string\n"
"          if(curx >= buffer_lines[cur_file_posy].size()) {\n"
"            curx = buffer_lines[cur_file_posy].size();\n"
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
"        }\n"
"\n"
"        //handle newlines by scrolling up and splitting buffer_lines\n"
"        else if(c == '\\r') {\n"
"          string line_start = buffer_lines[cur_file_posy].substr(0, curx);\n"
"          string line_end = buffer_lines[cur_file_posy].substr(curx, buffer_lines[cur_file_posy].size()-curx);\n"
"\n"
"          //rewrite the current line\n"
"          buffer_lines[cur_file_posy] = line_start;\n"
"          clrtoeol();\n"
"\n"
"          //add the new line\n"
"          buffer_lines.insert(buffer_lines.begin()+cur_file_posy+1, line_end);\n"
"\n"
"          //reprint all the buffer_lines after\n"
"          for(int i = cur_file_posy+1; i < buffer_lines.size(); i++) {\n"
"            if(i >= winy) {\n"
"              break;\n"
"            }\n"
"            move(cury+i-cur_file_posy, 0);\n"
"            clrtoeol();\n"
"            addstr(buffer_lines[i].c_str());\n"
"          }\n"
"\n"
"          //move the cursor down the cursor\n"
"          cur_file_posy++;\n"
"          cury++;\n"
"\n"
"          //scroll if the cursor passed the screen\n"
"          move(cury, 0);\n"
"          if(cury >= winy) {\n"
"            scroll(stdscr);\n"
"            cury = winy-1;\n"
"            addstr(buffer_lines[cur_file_posy].c_str());\n"
"            move(cury, 0);\n"
"          }\n"
"        }\n"
"\n"
"        //delete or backspace\n"
"        else if(c == 127 || c == 8) {\n"
"          if(curx > 0) {\n"
"            string line = buffer_lines[cur_file_posy];\n"
"            buffer_lines[cur_file_posy] = line.substr(0, curx-1) + line.substr(curx, line.size()-curx);\n"
"            cur_file_posx--;\n"
"            curx--;\n"
"            move(cury, curx);\n"
"            delch();\n"
"          }\n"
"          else if(cur_file_posy > 0) {\n"
"            int new_posx = buffer_lines[cur_file_posy-1].size();\n"
"            string bigger_line = buffer_lines[cur_file_posy-1] + buffer_lines[cur_file_posy];\n"
"            buffer_lines[cur_file_posy-1] = bigger_line;\n"
"            buffer_lines.erase(buffer_lines.begin()+cur_file_posy);\n"
"\n"
"            if(cury > 0) {\n"
"\n"
"              //reprint all buffer_lines after\n"
"              for(int i = cur_file_posy-1; i < buffer_lines.size(); i++) {\n"
"                if(i >= winy) {\n"
"                  break;\n"
"                }\n"
"                move(cury+i-cur_file_posy, 0);\n"
"                clrtoeol();\n"
"                addstr(buffer_lines[i].c_str());\n"
"              }\n"
"\n"
"              //move the cursor\n"
"              cur_file_posy--;\n"
"              cury--;\n"
"              move(cury, new_posx);\n"
"              cur_file_posx = new_posx;\n"
"            }\n"
"            else {\n"
"              move(cury, 0);\n"
"              clrtoeol();\n"
"              addstr(buffer_lines[cur_file_posy].c_str());\n"
"              move(cury, new_posx);\n"
"              cur_file_posx = new_posx;\n"
"            }\n"
"          }\n"
"        }\n"
"\n"
"        //regular character\n"
"        else {\n"
"\n"
"          //add the character to the line\n"
"          string line_end = (char)c + buffer_lines[cur_file_posy].substr(curx, buffer_lines[cur_file_posy].size()-curx);\n"
"          buffer_lines[cur_file_posy] = buffer_lines[cur_file_posy].substr(0, curx) + line_end;\n"
"          move(cury, curx);\n"
"          addstr(line_end.c_str());\n"
"\n"
"          curx++;\n"
"          cur_file_posx = curx;\n"
"          move(cury, curx);\n"
"        }\n"
"\n"
"        break;\n"
"      }\n"
"    }\n"
"  }\n"
"\n"
"  finish(0);\n"
"\n"
"  return 0;\n"
"}\n"
"\n"
"void rewrite_buffer() {\n"
"  clear();\n"
"  for(int i = 0; i < buffer_lines.size() && i < winy; i++) {\n"
"    move(i, 0);\n"
"    addstr(buffer_lines[i].c_str());\n"
"  }\n"
"  move(0, 0);\n"
"  cur_file_posy = 0;\n"
"  cur_file_posx = 0;\n"
"}\n"
"\n"
"static void finish(int sig) {\n"
"  endwin();\n"
"  exit(0);\n"
"}\n"
;
