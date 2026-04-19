#include <string>
#include "./users.h"

std::string commands(std::string str){
  str.erase(0,1);
  std::string command = str.substr(0,str.find(' '));
  std::string args = str.erase(0,str.find(' ')+1);
  return command + ">" + args;
}
