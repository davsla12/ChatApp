#include <enet/enet.h>
#include <stdio.h>
#include <string.h>

int main()
{
    if (enet_initialize() != 0) {
        printf("Chyba ENet\n");
        return 1;
    }

    atexit(enet_deinitialize);

    ENetHost* client = enet_host_create(NULL, 1, 2, 0, 0);

    if (!client) {
        printf("Nelze vytvořit klienta\n");
        return 1;
    }

    ENetAddress address;
    ENetEvent event;

    enet_address_set_host(&address, "127.0.0.1");
    address.port = 1234;

    ENetPeer* peer = enet_host_connect(client, &address, 2, 0);

    if (!peer) {
        printf("Nelze se připojit\n");
        return 1;
    }

    if (enet_host_service(client, &event, 5000) > 0 &&
        event.type == ENET_EVENT_TYPE_CONNECT)
    {
        printf("Připojeno k serveru\n");
    }
    else {
        printf("Timeout\n");
        enet_peer_reset(peer);
        return 1;
    }

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
