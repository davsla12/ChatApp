#include "../API.h"

#include "api.h"
#include "commands.h"

API_s api;

extern "C" int Version(){return 1;}
extern "C" void Free(void* ptr){free(ptr);}
extern "C" int Init(API_s apis){
  api = apis;
  api.commands.command_reg(&msg,"msg");
  return 0;
}
