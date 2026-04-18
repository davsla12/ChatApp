#include <enet/enet.h>
#include <stdlib.h>
#include <cstdio>
#include <cstring>

ENetHost* client;
ENetAddress address;
ENetPeer* peer;

ENetHost* sr_init(){
    if (enet_initialize() != 0) {
        printf("Chyba ENet\n");
        exit(1);
    }

    atexit(enet_deinitialize);

    client = enet_host_create(NULL, 1, 2, 0, 0);

    if (!client) {
        printf("Nelze vytvořit klienta\n");
        exit(1);
    }
    return client;
}

ENetPeer* sr_connect(){
    ENetAddress address;
    ENetEvent event;

    enet_address_set_host(&address, "127.0.0.1");
    address.port = 1234;

    peer = enet_host_connect(client, &address, 2, 0);

    if (!peer) {
        printf("Nelze se připojit\n");
        exit(1);
    }

    if (enet_host_service(client, &event, 5000) > 0 &&
        event.type == ENET_EVENT_TYPE_CONNECT)
    {
        printf("Připojeno k serveru\n");
    }
    else {
        printf("Timeout\n");
        enet_peer_reset(peer);
        exit(1);
    }
    return peer;
}

int send(const char* msg,int ChannelID){
    ENetPacket* packet = enet_packet_create(
        msg,
        strlen(msg) + 1,
        ENET_PACKET_FLAG_RELIABLE
    );

    return enet_peer_send(peer, ChannelID, packet);
}
