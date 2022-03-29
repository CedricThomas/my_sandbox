//
// Created by arzad on 23/02/2022.
//

#include <utility>
#include <csignal>
#include "world/World.hpp"

World::World(std::shared_ptr<TQueue<WorldEvent>> queue): _queue(std::move(queue)) {
}

World::~World() {
}

void World::generate() {
    unsigned short max_block = CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_HEIGHT;
    unsigned short number = CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_WIDTH;
    for (unsigned short i = number; i <= number; i += 16) {
        unsigned short data[] = {
                i, 1,
                static_cast<unsigned short>((max_block - i)), 0,
        };
        auto chunk = Chunk::unzip(data, CHUNK_WIDTH, CHUNK_HEIGHT, CHUNK_WIDTH);
        _queue->push(chunk);
        sleep(1);
    }
}
