//
// Created by arzad on 23/02/2022.
//

#include "server/Server.hpp"
#include "spdlog/spdlog.h"
#include "protocol/game/Deserialize.hpp"

Server::Server(std::shared_ptr<Topic<WorldEvent, GameEvent>> worldTopic, int port)
        : _worldTopic(worldTopic),
          _host() {
    ENetAddress address{};

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
    Event::RawEvent rawEvent;
    spdlog::info("start server");
    while (enet_host_service(_host, &event, 300) >= 0) {
        switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                event.peer->data = _worldTopic->createSyncSubscribe(
                        createRemoteGameSubscription((unsigned int) event.peer->connectID),
                        [event](const WorldEvent &gameEvent) {
                            auto rawEvent = gameEvent->serialize();
                            auto packet = enet_packet_create(
                                    rawEvent.getData(),
                                    rawEvent.getSize(),
                                    ENET_PROTOCOL_COMMAND_SEND_RELIABLE
                            );
                            spdlog::info("Sending World event of {} bytes of type {}", rawEvent.getSize(), rawEvent.getType());
                            return enet_peer_send(event.peer, 0, packet) == 0;
                        }
                ).get();
                spdlog::info("A new client connected");
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                // receive events from the clients and send them to the world
                rawEvent = Event::RawEvent(event.packet->dataLength, event.packet->data);
                spdlog::info("Receiving Game event of {} bytes of type {}", rawEvent.getSize(), rawEvent.getType());
                ((SyncSubscription<WorldEvent, GameEvent> *)event.peer->data)->pushToTopic(
                        GameEventsDeserializer.at(rawEvent.getType())(rawEvent)
                );
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                _worldTopic->removeSubscriber(
                        ((SyncSubscription<WorldEvent, GameEvent> *)event.peer->data)->getName()
                );
                event.peer->data = nullptr;
                spdlog::info("A client disconnected");
                break;
            case ENET_EVENT_TYPE_DISCONNECT_TIMEOUT:
                _worldTopic->removeSubscriber(
                        ((SyncSubscription<WorldEvent, GameEvent> *)event.peer->data)->getName()
                );
                event.peer->data = nullptr;
                spdlog::info("A client disconnected by timeout");
                break;
            case ENET_EVENT_TYPE_NONE:
                break;
        }
    }
}

Server::~Server() {
    enet_host_destroy(_host);
}
