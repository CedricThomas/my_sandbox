//
// Created by arzad on 04/05/2022.
//

#ifndef APP_UNLOADCHUNK_HPP
#define APP_UNLOADCHUNK_HPP

#include "glm/vec3.hpp"
#include "protocol/Event.hpp"

struct UnloadChunk: public Event {

    RawEvent serialize() override;

    void load(const RawEvent &event) override;

    EventType getType() const override;

    glm::vec3 position;
};


#endif //APP_UNLOADCHUNK_HPP
