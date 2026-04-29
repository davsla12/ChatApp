#include <enet/enet.h>
#include <stdio.h>
#include <string>

#include "./helpers.h"
#include "./users.h"
#include "./commands.h"

int main(){

  ENetHost* server = sr_init();

  ENetEvent event;

  while (1){
    while (enet_host_service(server, &event, 1000) > 0){
      switch (event.type){
        case ENET_EVENT_TYPE_CONNECT:
          //printf("Klient připojen\n");
          event.peer->data = new User;
          send(event.peer,"Zadej nickname: ");

          char ip[16];
          enet_address_get_host_ip(&event.peer->address, ip, sizeof(ip));
          printf("Klient %s:%u pripojen\n",ip,event.peer->address.port);
          fflush(stdout);

          break;

        case ENET_EVENT_TYPE_RECEIVE:{
          User* user = (User*)event.peer->data;
          if(!user->username.empty()){
            std::string arg((char*)event.packet->data,
                    event.packet->dataLength);

            arg = arg.c_str(); // důležité!

            printf("%s: %s\n", user->username.c_str(), arg.c_str());

            if (arg[0] == '/') {
              std::string buffer = command(arg);
              send(event.peer, buffer);
            }

            else{
              // echo zpět


              brodcastf(0,"%s: %.*s",user->username.c_str(),
                event.packet->dataLength,
                event.packet->data);
            }
            enet_packet_destroy(event.packet);
          }

          else{
            User* user = (User*)event.peer->data;
            std::string buffer = std::string((char*)event.packet->data,event.packet->dataLength-1);
            if(!nickname(nullptr,buffer))sendf(event.peer,0,"Neplatne jmeno: %s",buffer.c_str());
            else{
              std::vector<User> users = users_get();
              for(int i = 0;i < users.size();i++) if(users[i].username == buffer){
                send(event.peer,"Toto jmeno je zabrane",0);
                goto break_duplicit;
              }
              nickname(user,buffer);
              user->peer = event.peer;
              printf("Klient %s pripojen\n",buffer.c_str());
              brodcastf(0,"%s pripojen",buffer.c_str());
              sendf(event.peer,0,"Tvoje jmeno je %s",buffer.c_str());
              users_add(*user);
            }
          }
          break_duplicit:
          break;
        }

        case ENET_EVENT_TYPE_DISCONNECT: {
          User* user = (User*)event.peer->data;
          printf("Klient %s odpojen\n",user->username.c_str());
          brodcastf(0,"%s odpojen",user->username.c_str());
          users_rem(*user);
          delete (User*)event.peer->data;
          break;
        }

        default:
          break;
      }
    }
  }

  enet_host_destroy(server);
  return 0;
}
