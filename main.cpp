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

        //rewrite the program
        else if(c == 'w') {
          program_str = "";
          for(auto line : lines) {
            program_str += line + '\n';
          }
          rewrite_program(program_str);
        }

        //move the cursor around with hjkl
        else if(c == 'h' || c == 'j' || c == 'k' || c == 'l') {
          if(c == 'h') {
            if(cur_file_posx > 0) {
              cur_file_posx = curx-1;
              curx = cur_file_posx;
            }
          }
          else if(c == 'j') {
            if(cury < winy-1) {
              cur_file_posy++;
              cury++;
            }
            else if(cur_file_posy < lines.size()-1) {
              scroll(stdscr);
              cur_file_posy++;
              move(cury, 0);
              addstr(lines[cur_file_posy].c_str());
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
              addstr(lines[cur_file_posy].c_str());
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
          if(curx >= lines[cur_file_posy].size()) {
            curx = lines[cur_file_posy].size();
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

        //handle newlines by scrolling up and splitting lines
        else if(c == '\r') {
          string line_start = lines[cur_file_posy].substr(0, curx);
          string line_end = lines[cur_file_posy].substr(curx, lines[cur_file_posy].size()-curx);

          //rewrite the current line
          lines[cur_file_posy] = line_start;
          clrtoeol();

          //add the new line
          lines.insert(lines.begin()+cur_file_posy+1, line_end);

          //reprint all the lines after
          for(int i = cur_file_posy+1; i < lines.size(); i++) {
            if(i >= winy) {
              break;
            }
            move(cury+i-cur_file_posy, 0);
            clrtoeol();
            addstr(lines[i].c_str());
          }

          //move the cursor down the cursor
          cur_file_posy++;
          cury++;

          //scroll if the cursor passed the screen
          move(cury, 0);
          if(cury >= winy) {
            scroll(stdscr);
            cury = winy-1;
            addstr(lines[cur_file_posy].c_str());
            move(cury, 0);
          }
        }

        //delete or backspace
        else if(c == 127 || c == 8) {
          if(curx > 0) {
            string line = lines[cur_file_posy];
            lines[cur_file_posy] = line.substr(0, curx-1) + line.substr(curx, line.size()-curx);
            cur_file_posx--;
            curx--;
            move(cury, curx);
            delch();
          }
          else if(cur_file_posy > 0) {
            int new_posx = lines[cur_file_posy-1].size();
            string bigger_line = lines[cur_file_posy-1] + lines[cur_file_posy];
            lines[cur_file_posy-1] = bigger_line;
            lines.erase(lines.begin()+cur_file_posy);

            if(cury > 0) {

              //reprint all lines after
              for(int i = cur_file_posy-1; i < lines.size(); i++) {
                if(i >= winy) {
                  break;
                }
                move(cury+i-cur_file_posy, 0);
                clrtoeol();
                addstr(lines[i].c_str());
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
              addstr(lines[cur_file_posy].c_str());
              move(cury, new_posx);
              cur_file_posx = new_posx;
            }
          }
        }

        //regular character
        else {

          //add the character to the line
          string line_end = (char)c + lines[cur_file_posy].substr(curx, lines[cur_file_posy].size()-curx);
          lines[cur_file_posy] = lines[cur_file_posy].substr(0, curx) + line_end;
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
  return 0;
}

static void finish(int sig) {
  endwin();
  exit(0);
}
