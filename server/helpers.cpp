#include <enet/enet.h>
#include <stdio.h>
#include <string>

ENetHost* server;

ENetHost* sr_init(){
  if (enet_initialize() != 0) {
    fprintf(stderr, "Chyba inicializace ENet\n");
    exit(1);
  }

  atexit(enet_deinitialize);

  ENetAddress address;
  address.host = ENET_HOST_ANY;
  address.port = 1234;

  server = enet_host_create(
    &address,   // adresa
    32,         // max klientů
    2,          // kanály
    0,          // downstream limit
    0           // upstream limit
  );
  if (!server) {
    fprintf(stderr, "Nelze vytvořit server\n");
    exit(1);
  }

  printf("Server běží na portu 1234...\n");
  return server;
}

int send(ENetPeer* peer,std::string msg,int ChannelID){
    ENetPacket* packet = enet_packet_create(
        msg.c_str(),
        msg.size(),
        ENET_PACKET_FLAG_RELIABLE
    );

    return enet_peer_send(peer, ChannelID, packet);
}
