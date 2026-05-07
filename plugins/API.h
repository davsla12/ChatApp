#ifndef API_H
#define API_H

#include <MF/String.h>

#include "../server/users.h"

extern "C"{

typedef String (*CommandFunc)(const char* args, int user_id);

struct API_commands{
  int (* command_reg)(String (*func)(const char*,int),const char* name);
};

struct API_users{
  User* (*users_getbid)(int users_id);
  String (*users_getstr)();
};

struct API_s{
  API_commands commands;
  API_users users;
};
}//extern
#endif
