#ifndef USERS_H
#define USERS_H

#include <enet/enet.h>

#include <string>
#include <vector>

struct User{
  std::string username;
  ENetPeer* peer;
};

std::string commands(std::string str);

std::vector<User> users_get();
void users_add(User user);

#endif
