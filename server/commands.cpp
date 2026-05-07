#include <string>
#include <map>

#include <MF/String.h>
#include "../plugins/API.h"

#include "./commands.h"
#include "./users.h"
#include "./plugins.h"

std::map<std::string,CommandFunc> commands;

extern "C" int command_reg(String (*func)(const char*,int user_id),const char* name){
  if(!func){
    printf("Command %s dal nullptr",name);
  }
  std::string buff = std::string(name);
  printf("Novy command %s\n",buff.c_str());
  commands[buff] = func;
  return 0;
}

std::string command(std::string str,int user_id){
  str.erase(0,1);

  size_t pos = str.find(' ');

  std::string command;
  std::string args;
  String retval;

  if (pos == std::string::npos) {
    command = str;
    args = "";
  } else {
    command = str.substr(0, pos);
    args = str.substr(pos + 1);
  }

  auto it = commands.find(command);

  if (it == commands.end()) {
      return "Unknown command";
  }

  if (!it->second) {
      printf("Null function pointer!\n");
      return "Internal error";
  }

  retval = it->second(args.c_str(), user_id);

  std::string retstr(retval.data);
  Plugin_free(retval.data);
  return retstr;
}
