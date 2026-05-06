#include <stdio.h>
#include <MF/String.h>

#include "../API.h"

//Commands
extern "C" String ping(const char* args,int user_id){
  return (char*)"pong";
}

extern "C" String whoami(const char* args,int user_id){

}


extern "C" void Free(void* ptr){
free(ptr);
}
//Basic functions
extern "C" int Version(){return 1;}

extern "C" int Init(API_s api){
  api.commands.command_reg(&ping,"ping");
  return 0;
}
