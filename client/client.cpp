#include <enet/enet.h>
#include <stdio.h>
#include <string.h>
#include <MF/screen.h>

#include "./server.h"
#include "./Scanes/Hlavni.h"
#include "./Scanes/Log.h"

ENetEvent event;

int main(){

  ENetHost* client = sr_init();
  ENetPeer* peer = sr_connect();
  screen_init();
  atexit(screen_delete);
  SHlavni_init();
  SLog_init();
  screen_update();

  // pošli zprávu
  send("Hello world");
  send("Idk");

  // čekej na odpověď
  while(1){
    while (enet_host_service(client, &event, 50) > 0){
      if (event.type == ENET_EVENT_TYPE_RECEIVE) {
        Log("Server odpovedel: %s", event.packet->data);
        screen_update();
        enet_packet_destroy(event.packet);
      }
    }
  SInput();
  screen_update();
  }

  enet_peer_disconnect(peer, 0);
  enet_host_flush(client);
  enet_host_destroy(client);
  return 0;
}
