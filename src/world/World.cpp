//
// Created by arzad on 23/02/2022.
//

#include <utility>
#include "world/World.hpp"

World::World(std::shared_ptr<TQueue<Flat3DArray<short>>> queue): _queue(std::move(queue)) {
}

World::~World() {
}

void World::generate() {
    short data[] = {
        500, 0,
        500, 1,
    };
    _queue->push(Flat3DArray<short>::unzip(data, 10, 10, 10));
}
