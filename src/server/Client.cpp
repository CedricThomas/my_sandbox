//
// Created by arzad on 01/05/2022.
//
#include "server/Client.hpp"
#include "world/World.hpp"
#include "protocol/game/Deserialize.hpp"
#include "protocol/world/Deserialize.hpp"


Client::Client(
        std::shared_ptr<Topic<WorldEvent, GameEvent>> worldTopic,
        const std::string &address,
        int port) :
        _worldTopic(worldTopic),
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
    /* Connect to the remote adress. */
    enet_address_set_host(&enetAddress, address.c_str());
    enetAddress.port = port;
    /* Initiate the connection, allocating the two channels 0 and 1. */
    _peer = enet_host_connect(_host, &enetAddress, 2, 0);
    if (_peer == nullptr) {
        throw std::runtime_error("No available peers for initiating an ENet connection.");
    }
    ENetEvent event;
    if (enet_host_service(_host, &event, 3000) <= 0 || event.type != ENET_EVENT_TYPE_CONNECT) {
        /* Either the 5 seconds are up or a disconnect event was */
        /* received. Reset the peer in the event the 5 seconds   */
        /* had run out without any significant event.            */
        enet_peer_reset(_peer);
        throw std::runtime_error("Connection failed.");
    }
}

void Client::listenServer() {
    int status;
    ENetEvent event{};
    Event::RawEvent rawEvent{};
    while (!_disconnected && (status = enet_host_service(_host, &event, 10000)) >= 0) {
        if (status == 0) {
            continue;
        }
        switch (event.type) {
            case ENET_EVENT_TYPE_RECEIVE:
                // receive events from the world server
                rawEvent = Event::RawEvent(event.packet->dataLength, event.packet->data);
                spdlog::debug("Receiving world event of {} bytes of type {}", rawEvent.getSize(), rawEvent.getType());
                _worldTopic->publishToSubcribers(
                        WorldEventsDeserializer.at(rawEvent.getType())(rawEvent)
                );
                enet_packet_destroy(event.packet);
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                spdlog::warn("Disconnected.");
                _disconnected = true;
                break;
            case ENET_EVENT_TYPE_DISCONNECT_TIMEOUT:
                spdlog::warn("Timeout.");
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

void Client::listenGame() {
    while (!_disconnected) {
        // send game events to the world server
        Message<GameEvent> event;
        spdlog::debug("Pulling events...");
        if (!_worldTopic->tryPull(event)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            continue;
        }
        auto rawEvent = event.data->serialize();
        auto packet = enet_packet_create(
                rawEvent.getData(),
                rawEvent.getSize(),
                ENET_PACKET_FLAG_RELIABLE
        );
        spdlog::debug("Sending game event of {} bytes of type {}", rawEvent.getSize(), rawEvent.getType());
        enet_peer_send(_peer, 0, packet);
        enet_host_flush(_host);
    }
    spdlog::debug("Stop listen on game");
}

void Client::disconnect() {
    _disconnected = true;
}