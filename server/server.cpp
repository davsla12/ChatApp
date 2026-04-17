#include <enet/enet.h>
#include <stdio.h>

int main()
{
    if (enet_initialize() != 0) {
        fprintf(stderr, "Chyba inicializace ENet\n");
        return 1;
    }

    atexit(enet_deinitialize);

    ENetAddress address;
    address.host = ENET_HOST_ANY;
    address.port = 1234;

    ENetHost* server = enet_host_create(
        &address,   // adresa
        32,         // max klientů
        2,          // kanály
        0,          // downstream limit
        0           // upstream limit
    );

    if (!server) {
        fprintf(stderr, "Nelze vytvořit server\n");
        return 1;
    }

    printf("Server běží na portu 1234...\n");

    ENetEvent event;

    while (1)
    {
        while (enet_host_service(server, &event, 1000) > 0)
        {
            switch (event.type)
            {
                case ENET_EVENT_TYPE_CONNECT:
                    printf("Klient připojen\n");

                    break;

                case ENET_EVENT_TYPE_RECEIVE:{
                    printf("Zpráva: %s\n", event.packet->data);

                    // echo zpět
                    ENetPacket* reply = enet_packet_create(
                        event.packet->data,
                        event.packet->dataLength,
                        ENET_PACKET_FLAG_RELIABLE
                    );

                    enet_peer_send(event.peer, 0, reply);
                    enet_packet_destroy(event.packet);
                    break;
                }

                case ENET_EVENT_TYPE_DISCONNECT:
                    printf("Klient odpojen\n");
                    break;

                default:
                    break;
            }
        }
    }

    enet_host_destroy(server);
    return 0;
}
