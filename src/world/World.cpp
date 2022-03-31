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
    for (unsigned short i = number; i <= number; i += 1) {
        unsigned short data[] = {
                i, 1,
                static_cast<unsigned short>((max_block - i)), 0,
        };
        auto chunkData = Flat3DArray<unsigned short>::unzip(data, CHUNK_WIDTH, CHUNK_HEIGHT, CHUNK_WIDTH);
        Chunk chunk1 = {
                glm::vec3(0, 0, 0),
                chunkData,
        };
        _queue->push(chunk1);
        Chunk chunk2 = {
                glm::vec3(0, 0, 1),
                chunkData,
        };
        _queue->push(chunk2);
    }
}
