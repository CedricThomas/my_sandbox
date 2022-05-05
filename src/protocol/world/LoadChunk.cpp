//
// Created by arzad on 04/05/2022.
//

#include "protocol/world/LoadChunk.hpp"
#include "protocol/world/Types.hpp"

Event::RawEvent LoadChunk::serialize() {
    auto zip = data.zip();
    Event::RawEvent event(static_cast<unsigned int>(WorldEventType::LOAD_CHUNK), zip.first + sizeof(position));
    auto eventData = event.getData();
    std::memcpy(eventData, &position, sizeof(position));
    std::memcpy((unsigned char *)eventData + sizeof(position), zip.second, zip.first);
    return event;
}

void LoadChunk::load(const Event::RawEvent &event) {
    auto eventData = event.getData();
    std::memcpy(&position, eventData, sizeof(position));
    void *zip = (unsigned char *)eventData + sizeof(position);
    data = Flat3DArray<BlockTemplateBundledID>::unzip(zip);
}

EventType LoadChunk::getType() const {
    return static_cast<EventType>(WorldEventType::LOAD_CHUNK);
}
