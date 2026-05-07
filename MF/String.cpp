#include <stdlib.h>
#include <string>
#include <cstring>

#include "./String.h"

String String_std(const std::string& str) {
  String out;
  out.data = (char*)malloc(str.size() + 1);
  strcpy(out.data, str.c_str());
  out.size = str.size();
  return out;
}
