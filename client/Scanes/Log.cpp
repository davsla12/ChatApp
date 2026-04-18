#include <stdarg.h>
#include <vector>
#include <string>
#include <MF/screen.h>
#include "Log.h"

Scane SLog;
std::vector<std::string> log_buffer;

void Log(const char *fmt, ...) {
    char buf[1024];

    va_list args;
    va_start(args, fmt);

    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);

    log_buffer.push_back(buf);
}

void SLog_render(){
  for(int y = 0;y < log_buffer.size();y++){
    mvwprintw(SLog.window,y+1,1,"%s",log_buffer[y].c_str());
  }
}

int SLog_init(){
  CreateWin(&SLog,21,80,0,0);
  scrollok(SLog.window,TRUE);
  SLog.render = SLog_render;
  return AddScane(&SLog);
}
