//
// Created by arzad on 23/02/2022.
//

#include <utility>
#include "world/World.hpp"

World::World(std::shared_ptr<TQueue<WorldUpdate>> queue): _queue(std::move(queue)) {
}

World::~World() {
}

void World::generate() {
    unsigned short data[] = {
        30000, 0,
        30000, 1,
        5280, 0,
    };
    auto chunk = ChunkUpdate::unzip(data, 16, 16, 255);
    _queue->push(chunk);
}
