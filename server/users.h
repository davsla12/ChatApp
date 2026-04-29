#ifndef USERS_H
#define USERS_H

#include <enet/enet.h>

#include <string>
#include <vector>

struct User{
  int id = 1;
  std::string username;
  ENetPeer* peer;
};

std::vector<User*> users_get();
int users_add(User* user);
void users_rem(User user);
bool nickname(User* user,std::string nickname);

#endif
