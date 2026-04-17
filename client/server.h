#ifndef SERVER_H
#define SERVER_H

#include <enet/enet.h>

ENetHost* sr_init();
ENetPeer* sr_connect();

#endif
