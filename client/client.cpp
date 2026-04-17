#include <enet/enet.h>
#include <stdio.h>
#include <string.h>

#include "./server.h"

ENetEvent event;

int main()
{

    ENetHost* client = sr_init();
    ENetPeer* peer = sr_connect();

    // pošli zprávu
    const char* msg = "Ahoj ze clienta!";
    ENetPacket* packet = enet_packet_create(
        msg,
        strlen(msg) + 1,
        ENET_PACKET_FLAG_RELIABLE
    );

    enet_peer_send(peer, 0, packet);
    enet_host_flush(client);

    // čekej na odpověď
    while (enet_host_service(client, &event, 5000) > 0)
    {
        if (event.type == ENET_EVENT_TYPE_RECEIVE) {
            printf("Server odpověděl: %s\n", event.packet->data);
            enet_packet_destroy(event.packet);
            break;
        }
    }

    enet_peer_disconnect(peer, 0);

    enet_host_destroy(client);
    return 0;
}
