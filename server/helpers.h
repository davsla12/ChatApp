#ifndef HELPERS_H
#define HELPERS_H

ENetHost* sr_init();
int send(ENetPeer* peer,std::string msg,int ChannelID=0);

#endif
