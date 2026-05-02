#include <stdio.h>
#include <MF/String.h>

#include "../API.h"

//Commands
extern "C" String ping(const char* args,int user_id){
  return (char*)"pong";
}

extern "C" int Version(){return 1;}

extern "C" int Init(API_commands commands){
  commands.command_reg(&ping,"ping");
  return 0;
}
