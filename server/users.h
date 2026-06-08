#ifndef USERS_H
#define USERS_H

#include <enet/enet.h>
#include <MF/String.h>

#include <string>
#include <vector>

struct User{
  int id = 1;
  String username;
  ENetPeer* peer;
};

const std::vector<User*> users_get();
String users_getstr();
User users_getbid(int users_id);
int users_add(User* user);
void users_rem(int users_id);
bool nickname(User* user,std::string nickname);

#endif
