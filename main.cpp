#include <iostream>
#include <sstream>
#include <vector>
#include <curses.h>

using namespace std;

#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))

void rewrite_program(string str, vector<string> *lines);
void rewrite_buffer(int start, int x, int y);
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

//save the state of the program buffer
int pcurx, pcury;
int p_start_posy;

//keep track of the current position within the file
int cur_file_posx = 0;
int cur_file_posy = 0;

//set the size of the footer
int footer_height = 2;

int main(int argc, char *argv[]) {

  //get the initial coordinate positions
  for(int i = 0; i < argc; i++) {
    if(argv[i][0] == '+') {
      sscanf(argv[i], "+%d,%d,%d", &cur_file_posy, &cury, &curx);
    }
  }

  //create interrupt ^C to break
  signal(SIGINT, finish);

  //initialize library
  initscr();

  if(has_colors()) {
    //start_color();
    //init_pair(1, COLOR_GREEN, COLOR_BLACK);
    //attron(COLOR_PAIR(1));
  }

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
  winy = winy - footer_height;

  //get the buffer_lines from the program string
  istringstream program_str_stream(program_str);
  string line;
  while(getline(program_str_stream, line)) {
    program_lines.push_back(line);
  }
  buffer_lines.insert(buffer_lines.begin(), program_lines.begin(), program_lines.end());

  //print the screen with the program string
  rewrite_buffer(cur_file_posy, curx, cury);
  //for(int i = cur_file_posy; i < buffer_lines.size() && i-cur_file_posy < winy; i++) {
    //move(i-cur_file_posy, 0);
    //addstr(buffer_lines[i].c_str());
  //}
  //move(cury, curx);

  //infinitely loop over getting input
  int buffer_contents = it_buffer_program;
  for(;;) {
    getyx(stdscr, cury, curx);
    getmaxyx(stdscr, winy, winx);
    winy = winy - footer_height;

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
            string restart_str = "./it +" + to_string(cur_file_posy) + "," + to_string(cury) + "," + to_string(curx);
            system(restart_str.c_str());
            finish(0);
          }
        }

        //show compile output
        else if(c == 'o') {

          if(buffer_contents == it_buffer_program) {
            program_lines.clear();
            program_lines.insert(program_lines.begin(), buffer_lines.begin(), buffer_lines.end());
            buffer_lines.clear();
            buffer_lines.insert(buffer_lines.begin(), compile_output.begin(), compile_output.end());
            buffer_contents = it_buffer_compile_output;

            pcury = cury;
            pcurx = curx;
            p_start_posy = cur_file_posy;
            rewrite_buffer(0, 0, 0);
          }
          else if(buffer_contents == it_buffer_compile_output) {
            buffer_lines.clear();
            buffer_lines.insert(buffer_lines.begin(), program_lines.begin(), program_lines.end());
            buffer_contents = it_buffer_program;

            cury = pcury;
            curx = pcurx;
            rewrite_buffer(p_start_posy, curx, cury);
          }
        }

        //move the cursor around with hjkl
        else if(c == 'h' || c == 'j' || c == 'k' || c == 'l') {

          //remove any messages
          move(winy+footer_height-1, 0);
          clrtoeol();

          if(c == 'h') {
            if(cur_file_posx > 0) {
              cur_file_posx = curx-1;
              curx = cur_file_posx;
            }
          }
          else if(c == 'j') {
            if(cury < min(winy-1, buffer_lines.size()-1)) {
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

            //clear the footer lines
            for(int i = winy; i < winy+footer_height; i++) {
              move(i, 0);
              clrtoeol();
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
            if(cury+i-cur_file_posy >= winy) {
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
            move(cury, 0);
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
                if(cury+i-cur_file_posy+1 >= winy) {
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

void rewrite_buffer(int start, int x, int y) {
  clear();
  for(int i = start-y; i < buffer_lines.size() && i-start+y < winy; i++) {
    move(i-start+y, 0);
    addstr(buffer_lines[i].c_str());
  }
  move(y, x);
  cur_file_posy = start;
  cur_file_posx = x;
}

static void finish(int sig) {
  endwin();
  exit(0);
}
