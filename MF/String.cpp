#include <stdlib.h>
#include <string>
#include <cstring>

#include "./String.h"

String String_std(const std::string& str) {
  char* out = (char*)malloc(str.size() + 1);
  strcpy(out, str.c_str());
  return out;
}

int String_len(String str){
  if(str != nullptr)return strlen(str);
  return 0;
}
