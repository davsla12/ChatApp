#ifndef STRING_H
#define STRING_H

#include <string.h>
#include <string>

struct String{
  char * data;
  size_t size;
};

String String_std(const std::string& str);//convert from std::string
int String_len(String);

#endif
