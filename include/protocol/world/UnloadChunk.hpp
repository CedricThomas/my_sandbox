//
// Created by arzad on 04/05/2022.
//

#ifndef WORLD_UNLOADCHUNK_HPP
#define WORLD_UNLOADCHUNK_HPP

#include <memory>
#include "glm/vec2.hpp"
#include "protocol/Event.hpp"
#include "Events.hpp"

struct UnloadChunk: public Event {

    UnloadChunk() = default;

    UnloadChunk(glm::vec2 position);

    RawEvent serialize() override;

    void load(const RawEvent &event) override;

    EventType getType() const override;

    static WorldEvent deserialize(const RawEvent &event);

    glm::vec2 position;
};


#endif //WORLD_UNLOADCHUNK_HPP
