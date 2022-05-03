//
// Created by arzad on 23/02/2022.
//

#ifndef APP_WORLD_HPP
#define APP_WORLD_HPP

#include <memory>
#include "lib/broker/Topic.hpp"
#include "Events.hpp"
#include "application/game/Events.hpp"
#include "bundling/BundleAtlas.hpp"

#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 255

class World {
public:
    World(std::shared_ptr<Topic<WorldEvent, GameEvent>> worldEventTopic, std::shared_ptr<BundleAtlas>);

    void generate();

    void start();

    ~World();

private:
    std::shared_ptr<Topic<WorldEvent, GameEvent>> _worldEventTopic;
    std::shared_ptr<BundleAtlas> _bundleAtlas;
};


#endif //APP_WORLD_HPP
