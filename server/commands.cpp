#include <string>
#include <map>

#include "./commands.h"
#include "./users.h"

std::map<std::string,std::string(*)(std::string,int)> commands;

int command_reg(std::string (*func)(std::string args,int user_id),std::string name){
commands[name] = func;
return 0;
}

std::string whoami(std::string args,int user_id){
  User* user = users_getbid(user_id);
  if(user)return user->username;
  return "given id: " + std::to_string(user_id);
}

std::string list(std::string args,int user_id){
  std::string retval;
  std::vector<User*> users = users_get();
  for (int i = 0;i<users.size();i++){
    retval.append(users[i]->username);
    retval.append(";");
  }
  return retval;
}

std::string command(std::string str,int user_id){
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
  else if(command == "list") return list(args,user_id);
  else if(command == "whoami") return whoami(args,user_id);
  if(commands[command])return commands[command](args,user_id);
  return "Unknown command";
}
