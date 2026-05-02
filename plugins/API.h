#ifndef API_H
#define API_H

#include <MF/String.h>

extern "C"{

typedef char* (*CommandFunc)(const char*, int);

struct API_commands{
  int (* command_reg)(String (*func)(const char*,int),const char* name);
};

}
#endif
