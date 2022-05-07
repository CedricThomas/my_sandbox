//
// Created by arzad on 04/05/2022.
//

#include "protocol/world/LoadChunk.hpp"
#include "protocol/world/Types.hpp"
#include "protocol/world/Events.hpp"


LoadChunk::LoadChunk(const glm::vec3 &position, const Flat3DArray<BlockTemplateBundledID> &data)
        : position(position),
          data(data) {}

Event::RawEvent LoadChunk::serialize() {
    auto zip = data.zip();
    Event::RawEvent event(
            zip.first + sizeof(position),
            static_cast<unsigned int>(WorldEventType::LOAD_CHUNK)
    );
    auto eventData = event.getPayload();
    std::memcpy(eventData, &position, sizeof(position));
    std::memcpy(((unsigned char *) eventData) + sizeof(position), zip.second, zip.first);
    return event;
}

void LoadChunk::load(const Event::RawEvent &event) {
    auto eventData = event.getPayload();
    std::memcpy(&position, eventData, sizeof(position));
    auto zipSize = event.getPayloadSize() - sizeof(position);
    void *zip = (unsigned char *)eventData + sizeof(position);
    data = Flat3DArray<BlockTemplateBundledID>::unzip(zipSize, zip);
}

EventType LoadChunk::getType() const {
    return static_cast<EventType>(WorldEventType::LOAD_CHUNK);
}

WorldEvent LoadChunk::deserialize(const Event::RawEvent &rawEvent) {
    auto *event = new LoadChunk();
    event->load(rawEvent);
    return std::shared_ptr<Event>(event);
}
