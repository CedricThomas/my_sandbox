//
// Created by arzad on 04/05/2022.
//

#ifndef APP_EVENT_HPP
#define APP_EVENT_HPP

using EventType = unsigned short;

class Event {
public:

    class RawEvent {
    public:
        explicit RawEvent(unsigned int size, void *data);

        explicit RawEvent(unsigned int size, EventType type);

        void *getData() const;

        unsigned int getSize() const;

        EventType getType() const;

    private:
        unsigned int _size;
        void *_data;
    };

    virtual EventType getType() const = 0;

    virtual RawEvent serialize() = 0;

    virtual void load(const RawEvent &event) = 0;
};


#endif //APP_EVENT_HPP
