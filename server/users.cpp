#include <string>
#include "./users.h"

std::vector<User> Users;

std::string commands(std::string str){
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
  return command + ">" + args;
}
std::vector<User> users_get(){
  return Users;
}

void users_add(User user){
  Users.push_back(user);
  //printf("Uzivatel %s pridan\n",user.username);
}
void users_rem(User user){
  for(int i = 0;i<Users.size();i++){
    if(Users[i].username == user.username){
      Users.erase(Users.begin() + i);
      break;
    }
  }
}
