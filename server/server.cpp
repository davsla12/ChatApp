#include <enet/enet.h>
#include <stdio.h>
#include <string>

#include "./helpers.h"
#include "./users.h"

int main(){

  ENetHost* server = sr_init();

  ENetEvent event;

  while (1){
    while (enet_host_service(server, &event, 1000) > 0){
      switch (event.type){
        case ENET_EVENT_TYPE_CONNECT:
          printf("Klient připojen\n");
          event.peer->data = new User;

          break;

        case ENET_EVENT_TYPE_RECEIVE:{
          User* user = (User*)event.peer->data;
          if(!user->username.empty()){
          printf("Zpráva: %s\n", event.packet->data);

          std::string buffer;
          if(event.packet->data[0] == '/'){
            std::string arg = std::string((char*)event.packet->data,event.packet->dataLength);
            buffer = commands(arg);
            send(event.peer,buffer);
          }

          else{
            // echo zpět
            ENetPacket* reply = enet_packet_create(
              event.packet->data,
              event.packet->dataLength,
              ENET_PACKET_FLAG_RELIABLE
            );

            //enet_peer_send(event.peer, 0, reply);
            enet_host_broadcast(server, 0, reply);
          }
          enet_packet_destroy(event.packet);
          }

          else{
            User* user = (User*)event.peer->data;
            std::string buffer = std::string((char*)event.packet->data,event.packet->dataLength);
            user->username = buffer;
          }

          break;
        }

        case ENET_EVENT_TYPE_DISCONNECT:
          printf("Klient odpojen\n");
          delete (User*)event.peer->data;
          break;

        default:
          break;
      }
    }
  }

  enet_host_destroy(server);
  return 0;
}
