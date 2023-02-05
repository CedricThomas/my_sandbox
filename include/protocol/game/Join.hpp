//
// Created by arzad on 05/05/2022.
//

#ifndef APP_JOIN_HPP
#define APP_JOIN_HPP

#include <memory>
#include "glm/vec3.hpp"
#include "protocol/Event.hpp"
#include "Events.hpp"

struct Join: public Event {

    Join() = default;

    Join(const glm::vec3 &position);

    RawEvent serialize() override;

    void load(const RawEvent &event) override;

    EventType getType() const override;

    static GameEvent deserialize(const RawEvent &event);

    glm::vec3 position;
};

#endif //APP_JOIN_HPP
