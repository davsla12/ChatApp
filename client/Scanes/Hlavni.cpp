#include <string>
#include <MF/screen.h>
#include "../server.h"

#define BUFFER_SIZE 33

Scane SHlavni;

bool running = true;
std::string buffer;
int buffer_pos = 0;

bool Run(){
  return running;
}

void SHlavni_input(int key){
  if(key == '\n'){
    if(buffer == "\\quit") running = false;
    else send(buffer.c_str());
    buffer = "";
    buffer_pos = 0;
  }
  else if(key >-1 && key<256 && buffer.size() < BUFFER_SIZE){
    buffer.insert(buffer_pos,1,key);
    buffer_pos++;
  }

  else if(key == KEY_RIGHT && buffer_pos < buffer.size() && buffer_pos < BUFFER_SIZE) buffer_pos++;
  else if(key == KEY_LEFT && buffer_pos) buffer_pos--;
  else if(key == KEY_BACKSPACE && buffer_pos){
    buffer.erase(buffer_pos-1,1);
    buffer_pos--;
  }
}

void SHlavni_render(){
  mvwprintw(SHlavni.window,1,1,"%s",buffer.c_str());
  if (buffer_pos < buffer.size()) {
    wattron(SHlavni.window,A_REVERSE);
    mvwaddch(SHlavni.window,1,buffer_pos+1,buffer[buffer_pos]);
    wattroff(SHlavni.window,A_REVERSE);
  } else {
    // kurzor na konci (prázdné místo)
    wattron(SHlavni.window, A_REVERSE);
    mvwaddch(SHlavni.window, 1, buffer_pos + 1, ' ');
    wattroff(SHlavni.window, A_REVERSE);
}
}

int SHlavni_init(){
//  for(int i = 0;i < sizeof(buffer)-1;i++)buffer[i] = ' ';
  int maxY = GetSizey(0);
  int maxX = GetSizex(0);
  CreateWin(&SHlavni,3,40,maxY-3,0);
  SHlavni.input = SHlavni_input;
  SHlavni.render = SHlavni_render;
  return AddScane(&SHlavni);
}
