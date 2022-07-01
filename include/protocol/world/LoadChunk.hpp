//
// Created by arzad on 04/05/2022.
//

#ifndef WORLD_LOADCHUNK_HPP
#define WORLD_LOADCHUNK_HPP

#include "glm/vec2.hpp"
#include "protocol/Event.hpp"
#include "bundling/Bundle.hpp"
#include "lib/containers/Flat3DArray.hpp"
#include "Events.hpp"

struct LoadChunk: public Event {

    LoadChunk(const glm::vec2 &position, const Flat3DArray<BlockTemplateBundledID> &data);

    LoadChunk() = default;

    RawEvent serialize() override;

    void load(const RawEvent &event) override;

    EventType getType() const override;

    static WorldEvent deserialize(const RawEvent &event);

    glm::vec2 position;
    Flat3DArray<BlockTemplateBundledID> data;
};


#endif //WORLD_LOADCHUNK_HPP
