#ifndef STRING_H
#define STRING_H

#include <string>

using String = char*;

String String_std(const std::string& str);//convert from std::string
int String_len(String);

#endif
