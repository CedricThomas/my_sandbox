//
// Created by arzad on 01/05/2022.
//
#include "server/Client.hpp"
#include "world/World.hpp"
#include "protocol/game/Deserialize.hpp"


Client::Client(std::shared_ptr<Topic<WorldEvent, GameEvent>> worldTopic,
               std::shared_ptr<ASubscription<WorldEvent, GameEvent>> gameSubscription, const std::string &address,
               int port) :
        _worldTopic(worldTopic),
        _gameSubscription(gameSubscription),
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

void Client::listenServer() {
    ENetEvent event;
    Event::RawEvent rawEvent;
    while (enet_host_service(_host, &event, 3000) > 0) {
        switch (event.type) {
            case ENET_EVENT_TYPE_RECEIVE:
                rawEvent = Event::RawEvent(event.packet->dataLength, event.packet->data);
                _worldTopic->push(
                        Message<WorldEvent>{
                                "Server",
                                GameEventsDeserializer.at(rawEvent.getType())(rawEvent)
                        }
                );
                enet_packet_destroy(event.packet);
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                puts("Disconnection succeeded.");
                _disconnected = true;
                return;
            case ENET_EVENT_TYPE_DISCONNECT_TIMEOUT:
                _disconnected = true;
                return;
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

void Client::listenGame() {
    while (_disconnected) {
        GameEvent event;
        _gameSubscription->pull(event);
        auto rawEvent =  event->serialize();
        auto packet = enet_packet_create(rawEvent.getData(), rawEvent.getSize(), ENET_PACKET_FLAG_RELIABLE);
        enet_peer_send(_peer, 0, packet);
    }
}
