#ifndef COMMANDS_H
#define COMMANDS_H

#include <MF/String.h>

extern "C" int command_reg(String (*func)(const char *,int),const char* name);
std::string command(std::string str,int user_id);

#endif
