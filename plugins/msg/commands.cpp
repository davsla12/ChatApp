#include <string>
#include <MF/String.h>

#include "api.h"

extern "C" String msg(const char* args,int user_id){
  std::string strArgs(args);
  size_t firstSpace = strArgs.find(' ');
  std::string name;
  std::string msg;

  if (firstSpace != std::string::npos) {
    name = strArgs.substr(0, firstSpace);

    msg = strArgs.substr(firstSpace + 1);
  } else {
    return String_std("nezadal jsi zpravu");
  }

  String Slist = api.users.users_getstr();
  char* token = strtok(Slist.data,";");
  while(token != NULL){
    int cislo = atoi(token);
    if(std::string(api.users.users_getbid(cislo).username.data) == name){
      api.helpers.send_bid(cislo,String_std(msg),0);
      return String_std("Poslano");
    }
    token = strtok(NULL,";");
  }
  return String_std("Uzivatel nenalezen");
}
