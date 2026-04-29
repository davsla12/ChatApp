#include <iostream>
#include <string>
#include "./users.h"

int IDs = 0;//0 is server

std::vector<User*> Users;

std::vector<User*> users_get(){
  return Users;
}

int users_add(User* user){
  user->id = ++IDs;
  Users.push_back(user);
  return IDs;
  //printf("Uzivatel %s pridan\n",user.username);
}
void users_rem(User user){
  for(int i = 0;i<Users.size();i++){
    if(Users[i]->username == user.username){
      Users.erase(Users.begin() + i);
      break;
    }
  }
}

bool nickname(User* user,std::string nickname){
  bool retval = true;
  for(int i = 0;i < nickname.size() && nickname[i]!='\0';i++){
    if(nickname[i]>='a' && nickname[i]<='z'){}
    else if(nickname[i]>='A' && nickname[i]<='Z'){}
    else if(nickname[i]>='0' && nickname[i]<='9'){}
    else if(nickname[i]=='_'){}
    else retval = false;
  }
  if(retval&&user)user->username = nickname;
  return retval;
}
