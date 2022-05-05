//
// Created by arzad on 04/05/2022.
//

#ifndef APP_LOADCHUNK_HPP
#define APP_LOADCHUNK_HPP

#include "glm/vec3.hpp"
#include "protocol/Event.hpp"
#include "bundling/Bundle.hpp"
#include "lib/containers/Flat3DArray.hpp"

struct LoadChunk: public Event {

    RawEvent serialize() override;

    void load(const RawEvent &event) override;

    EventType getType() const override;

    glm::vec3 position;
    Flat3DArray<BlockTemplateBundledID> data;
};


#endif //APP_LOADCHUNK_HPP
