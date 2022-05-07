//
// Created by arzad on 04/05/2022.
//
#include "protocol/Event.hpp"

Event::RawEvent::RawEvent(size_t size, void *data) {
    this->_size = size - sizeof(EventType);
    this->_data = data;
}

Event::RawEvent::RawEvent(size_t payloadSize, EventType type) {
    this->_size = payloadSize;
    this->_data = new unsigned char[payloadSize + sizeof(EventType)];
    ((EventType *)this->_data)[0] = type;
}

void *Event::RawEvent::getPayload() const {
    return ((EventType *)_data) + 1;
}

size_t Event::RawEvent::getPayloadSize() const {
    return this->_size;
}

EventType Event::RawEvent::getType() const {
    return *((EventType *) this->_data);
}

void *Event::RawEvent::getData() const {
    return _data;
}

size_t Event::RawEvent::getSize() const {
    return this->_size + sizeof(EventType);
}
