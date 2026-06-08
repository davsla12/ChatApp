#include <stdio.h>
#include <sstream>
#include <string>
#include <MF/String.h>

#include "../API.h"

API_s api;

//Commands
extern "C" String ping(const char* args,int user_id){
  return String_std("pong");
}

extern "C" String whoami(const char* args,int user_id){
  User user = api.users.users_getbid(user_id);
  if(user.id>=0)return user.username;

  std::string tmp = "given id:" + std::to_string(user_id);
  return String_std(tmp);
}

extern "C" String list(const char* args,int user_id){
  std::string retval;

  String Slist = api.users.users_getstr();

  char* token = strtok(Slist.data,";");
  while(token != NULL){
    int cislo = atoi(token);
    retval.append(std::string(api.users.users_getbid(cislo).username.data));
    retval.append(";");
    token = strtok(NULL,";");
  }

  return String_std(retval);
}

extern "C" void Free(void* ptr){
free(ptr);
}
//Basic functions
extern "C" int Version(){return 1;}

extern "C" int Init(API_s apis){
  api = apis;
  api.commands.command_reg(&ping,"ping");
  api.commands.command_reg(&whoami,"whoami");
  api.commands.command_reg(&list,"list");
  return 0;
}
