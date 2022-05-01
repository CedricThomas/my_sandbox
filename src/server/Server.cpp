//
// Created by arzad on 23/02/2022.
//

#include <cstdio>
#include <iostream>
#define ENET_IMPLEMENTATION
#include "lib/enet.h"
#include "server/Server.hpp"

void Server::client() {
    ENetHost* client;
    client = enet_host_create(nullptr /* create a client host */,
                              1 /* only allow 1 outgoing connection */,
                              2 /* allow up 2 channels to be used, 0 and 1 */,
                              0 /* assume any amount of incoming bandwidth */,
                              0 /* assume any amount of outgoing bandwidth */);
    if (client == nullptr) {
        fprintf(stderr,
                "An error occurred while trying to create an ENet client host.\n");
        exit(EXIT_FAILURE);
    }

    ENetAddress address = { 0 };
    ENetEvent event = { };
    ENetPeer* peer;
    /* Connect to some.server.net:1234. */
    enet_address_set_host(&address, "127.0.0.1");
    address.port = 7777;
    /* Initiate the connection, allocating the two channels 0 and 1. */
    peer = enet_host_connect(client, &address, 2, 0);
    if (peer == NULL) {
        fprintf(stderr,
                "No available peers for initiating an ENet connection.\n");
        exit(EXIT_FAILURE);
    }
    /* Wait up to 5 seconds for the connection attempt to succeed. */
    if (enet_host_service(client, &event, 5000) > 0 &&
        event.type == ENET_EVENT_TYPE_CONNECT) {
        puts("Connection to some.server.net:1234 succeeded.");
    } else {
        /* Either the 5 seconds are up or a disconnect event was */
        /* received. Reset the peer in the event the 5 seconds   */
        /* had run out without any significant event.            */
        enet_peer_reset(peer);
        puts("Connection to some.server.net:1234 failed.");
    }
    ENetPacket *packet = enet_packet_create ("packet", strlen ("packet") + 1, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send (peer, 0, packet);

    // Receive some events
    enet_host_service(client, &event, 5000);

    // Disconnect
    enet_peer_disconnect(peer, 0);

    uint8_t disconnected = false;
    /* Allow up to 3 seconds for the disconnect to succeed
     * and drop any packets received packets.
     */
    while (enet_host_service(client, &event, 3000) > 0) {
        switch (event.type) {
            case ENET_EVENT_TYPE_RECEIVE:
                enet_packet_destroy(event.packet);
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                puts("Disconnection succeeded.");
                disconnected = true;
                break;
            case ENET_EVENT_TYPE_NONE:
                break;
            case ENET_EVENT_TYPE_CONNECT:
                break;
            case ENET_EVENT_TYPE_DISCONNECT_TIMEOUT:
                break;
        }
    }

    // Drop connection, since disconnection didn't successed
    if (!disconnected) {
        enet_peer_reset(peer);
    }

    enet_host_destroy(client);
}

void Server::server() {

    ENetAddress address = {0};

    address.host = ENET_HOST_ANY; /* Bind the server to the default localhost.     */
    address.port = 7777; /* Bind the server to port 7777. */

    #define MAX_CLIENTS 32

    /* create a server */
    ENetHost * server = enet_host_create(&address, MAX_CLIENTS, 2, 0, 0);

    if (server == nullptr) {
        printf("An error occurred while trying to create an ENet server host.\n");
        exit(1);
    }

    printf("Started a server...\n");

    ENetEvent event;
    int resp;
    /* Wait up to 1000 milliseconds for an event. (WARNING: blocking) */
    while ((resp = enet_host_service(server, &event, 1000)) >= 0) {
        switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                printf("A new client connected from %x:%u.\n",  event.peer->address.host, event.peer->address.port);
                /* Store any relevant client information here. */
                event.peer->data = new std::string("Client information");
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                printf("A packet of length %lu containing %s was received from %s on channel %u.\n",
                       event.packet->dataLength,
                       event.packet->data,
                       ((std::string *)event.peer->data)->c_str(),
                       event.channelID);
                /* Clean up the packet now that we're done using it. */
                enet_packet_destroy (event.packet);
                break;

            case ENET_EVENT_TYPE_DISCONNECT:
                printf("%s disconnected.\n", ((std::string *)event.peer->data)->c_str());
                /* Reset the peer's client information. */
                delete ((std::string *)event.peer->data);
                break;

            case ENET_EVENT_TYPE_DISCONNECT_TIMEOUT:
                printf("%s disconnected due to timeout.\n", ((std::string *)event.peer->data)->c_str());
                /* Reset the peer's client information. */
                delete ((std::string *)event.peer->data);
                break;

            case ENET_EVENT_TYPE_NONE:
                break;
        }
    }
    std::cout << "Server stopped: " << resp << std::endl;

    enet_host_destroy(server);
}

void Server::init() {
    if (enet_initialize() != 0) {
        throw std::runtime_error("An error occurred while initializing ENet.");
    }
    atexit(enet_deinitialize);
}
