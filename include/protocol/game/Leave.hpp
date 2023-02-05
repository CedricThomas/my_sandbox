//
// Created by arzad on 05/05/2022.
//

#ifndef APP_LEAVE_HPP
#define APP_LEAVE_HPP

#include <memory>
#include "glm/vec3.hpp"
#include "protocol/Event.hpp"
#include "Events.hpp"

struct Leave: public Event {

    Leave() = default;

    RawEvent serialize() override;

    void load(const RawEvent &event) override;

    EventType getType() const override;

    static GameEvent deserialize(const RawEvent &event);
};

#endif //APP_LEAVE_HPP
