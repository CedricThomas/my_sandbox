//
// Created by arzad on 04/05/2022.
//

#ifndef WORLD_UNLOADCHUNK_HPP
#define WORLD_UNLOADCHUNK_HPP

#include <memory>
#include "glm/vec3.hpp"
#include "protocol/Event.hpp"
#include "Events.hpp"

struct UnloadChunk: public Event {

    RawEvent serialize() override;

    void load(const RawEvent &event) override;

    EventType getType() const override;

    static WorldEvent deserialize(const RawEvent &event);

    glm::vec3 position;
};


#endif //WORLD_UNLOADCHUNK_HPP