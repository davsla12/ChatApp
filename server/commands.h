#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>

int command_reg(std::string (*func)(),std::string name);
std::string command(std::string str);

#endif
