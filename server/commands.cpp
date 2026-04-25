#include <string>

#include "./commands.h"

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
  return command + ">" + args;
}
