#ifndef COMMANDS_H
#define COMMANDS_H

#include <MF/String.h>

struct Command{
  int id;
  String name;//or std::string idk now
  String (*func)(const char *,int);
};

extern "C" int command_reg(String (*func)(const char *,int),const char* name);
std::string command(std::string str,int user_id);

#endif
