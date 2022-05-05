//
// Created by arzad on 23/02/2022.
//

#include "server/Server.hpp"

Server::Server(std::shared_ptr<Topic<WorldEvent, GameEvent>> worldTopic, int port)
        : _worldTopic(worldTopic),
          _host() {
    ENetAddress address {};

    address.host = ENET_HOST_ANY; /* Bind the server to the default localhost.     */
    address.port = port; /* Bind the server to port 7777. */

    /* create a server */
    _host = enet_host_create(&address, MAX_CLIENTS, 2, 0, 0);
    if (_host == nullptr) {
        throw std::runtime_error("An error occurred while trying to create an ENet server host.");
    }

}

void Server::start() {
    ENetEvent event;
    std::cout << "start" << std::endl;
    while (enet_host_service(_host, &event, 300) >= 0) {
        switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                std::cout << "A new client connected" << std::endl;
            case ENET_EVENT_TYPE_RECEIVE:
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                std::cout << "A client disconnected" << std::endl;
                break;
            case ENET_EVENT_TYPE_DISCONNECT_TIMEOUT:
                std::cout << "A client disconnected by timeout" << std::endl;
                break;
            case ENET_EVENT_TYPE_NONE:
                break;
        }
    }

//
//        std::cout << "update" << std::endl;
//        WorldEvent serverEvent;
//        auto hasElem = _subscription->tryPull(serverEvent);
//        if (!hasElem) {
//            continue;
//        }
//        auto chunk = std::get<Chunk>(serverEvent);
//        auto size = sizeof(BlockTemplateBundledID) * chunk.data.size() + sizeof(chunk.position);
//        auto data = new unsigned char[size];
//        std::memcpy(data, &chunk.position, sizeof(chunk.position));
//        std::memcpy(data + sizeof(chunk.position), (const void *) &(chunk.data.getData()[0]), sizeof(BlockTemplateBundledID) * chunk.data.size());
//        ENetPacket *packet = enet_packet_create (data, size, ENET_PACKET_FLAG_RELIABLE);
////        std::cout << "sending : " << sizeof(serverEvent) << std::endl;
//        for (size_t i = 0; i < _host->connectedPeers; i++) {
//            enet_peer_send(&_host->peers[i], 0, packet);
//            enet_host_flush(_host);
//        }
//    std::cout << "server end" << std::endl;
}