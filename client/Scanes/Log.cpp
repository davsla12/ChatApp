#include <stdarg.h>
#include <vector>
#include <string>
#include <MF/screen.h>
#include "Log.h"

Scane SLog;
std::vector<std::string> log_buffer;

void Log(const char *fmt, ...) {
    int screen_y = GetSizey(SLog.ID)-2;
    char buf[1024];

    va_list args;
    va_start(args, fmt);

    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);

    log_buffer.push_back(buf);
    if(log_buffer.size()>screen_y)log_buffer.erase(log_buffer.begin());
}

void SLog_render(){
  int screen_y = GetSizey(SLog.ID)-2;
  for(int y = log_buffer.size()-1;y >= 0;y--){
    mvwprintw(SLog.window,(screen_y-log_buffer.size())+y+1,1,"%s",log_buffer[y].c_str());
  }
}

int SLog_init(){
  CreateWin(&SLog,21,80,0,0);
  scrollok(SLog.window,TRUE);
  SLog.render = SLog_render;
  return AddScane(&SLog);
}
