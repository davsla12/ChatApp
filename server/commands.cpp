#include <string>
#include <map>

#include "./commands.h"
#include "./users.h"

std::map<std::string,std::string(*)()> commands;

int command_reg(std::string (*func)(),std::string name){
commands[name] = func;
return 0;
}

std::string list(){
  std::string retval;
  std::vector<User> users = users_get();
  for (int i = 0;i<users.size();i++){
    retval.append(users[i].username);
    retval.append(";");
  }
  return retval;
}

std::string command(std::string str){
  str.erase(0,1);

  size_t pos = str.find(' ');

  std::string command;
  std::string args;

  if (pos == std::string::npos) {
    command = str;
    args = "";
  } else {
    command = str.substr(0, pos);
    args = str.substr(pos + 1);
  }

  if(command == "ping") return "pong";
  else if(command == "list") return list();
  if(commands[command])return commands[command]();
  return "Unknown command";
}
