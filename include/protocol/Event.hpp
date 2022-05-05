//
// Created by arzad on 04/05/2022.
//

#ifndef APP_EVENT_HPP
#define APP_EVENT_HPP

#include <cstddef>

using EventType = unsigned short;

class Event {
public:

    class RawEvent {
    public:
        RawEvent() = default;

        explicit RawEvent(size_t size, void *data);

        explicit RawEvent(size_t size, EventType type);

        void *getData() const;

        size_t getSize() const;

        EventType getType() const;

    private:
        size_t _size;
        void *_data;
    };

    virtual EventType getType() const = 0;

    virtual RawEvent serialize() = 0;

    virtual void load(const RawEvent &event) = 0;
};


#endif //APP_EVENT_HPP
