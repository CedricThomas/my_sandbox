//
// Created by arzad on 01/05/2022.
//
#include "server/Client.hpp"
#include "world/World.hpp"

Client::Client(std::shared_ptr<Topic<WorldEvent, GameEvent>> topic, const std::string &address, int port) :
        _topic(topic),
        _host(),
        _peer(),
        _disconnected(false) {
    _host = enet_host_create(
            nullptr /* create a client host */,
            1 /* only allow 1 outgoing connection */,
            2 /* allow up 2 channels to be used, 0 and 1 */,
            0 /* assume any amount of incoming bandwidth */,
            0 /* assume any amount of outgoing bandwidth */
    );
    if (_host == nullptr) {
        throw std::runtime_error("An error occurred while trying to create an ENet client host.");
    }

    ENetAddress enetAddress;
    /* Connect to some.server.net:1234. */
    enet_address_set_host(&enetAddress, address.c_str());
    enetAddress.port = port;
    /* Initiate the connection, allocating the two channels 0 and 1. */
    _peer = enet_host_connect(_host, &enetAddress, 2, 0);
    if (_peer == nullptr) {
        throw std::runtime_error("No available peers for initiating an ENet connection.");
    }
    ENetEvent event;
    if (enet_host_service(_host, &event, 5000) <= 0 || event.type != ENET_EVENT_TYPE_CONNECT) {
        /* Either the 5 seconds are up or a disconnect event was */
        /* received. Reset the peer in the event the 5 seconds   */
        /* had run out without any significant event.            */
        enet_peer_reset(_peer);
        throw std::runtime_error("Connection failed.");
    }
}

void Client::start() {
    ENetEvent event;

    while (enet_host_service(_host, &event, 3000) > 0) {
        switch (event.type) {
            case ENET_EVENT_TYPE_RECEIVE:
                [&]() {
                    Chunk chunk {
                            glm::vec3(0, 0, 0),
                            Flat3DArray<BlockTemplateBundledID>(CHUNK_WIDTH, CHUNK_HEIGHT, CHUNK_WIDTH)
                    };

                    std::memcpy(&chunk.position, event.packet->data, sizeof chunk.position);
                    std::memcpy((void *) &(chunk.data.getData()[0]), event.packet->data + sizeof chunk.position, sizeof(BlockTemplateBundledID) * chunk.data.size());
                    _topic.get()->publishToSubcribers(chunk);
                    /* Clean up the packet now that we're done using it. */
                    enet_packet_destroy(event.packet);
                }();
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                puts("Disconnection succeeded.");
                _disconnected = true;
                break;
            case ENET_EVENT_TYPE_DISCONNECT_TIMEOUT:
                _disconnected = true;
                break;
            default:
                break;

        }
    }
}

Client::~Client() {
    if (!_disconnected) {
        enet_peer_reset(_peer);
    }

    enet_host_destroy(_host);
}
