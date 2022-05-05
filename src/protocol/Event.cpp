//
// Created by arzad on 04/05/2022.
//
#include "protocol/Event.hpp"

Event::RawEvent::RawEvent(unsigned int size, void *data) {
    this->_size = size;
    this->_data = data;
}

Event::RawEvent::RawEvent(unsigned int size, EventType type) {
    this->_size = size;
    this->_data = new unsigned char[size + sizeof(EventType)];
    ((EventType *)this->_data)[0] = type;
}

void *Event::RawEvent::getData() const {
    return ((EventType *)_data + 1);
}

unsigned int Event::RawEvent::getSize() const {
    return this->_size;
}

EventType Event::RawEvent::getType() const {
    return *((EventType *) this->_data);
}
