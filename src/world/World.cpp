//
// Created by arzad on 23/02/2022.
//

#include <utility>
#include <csignal>
#include "world/World.hpp"
#include "bundling/DefaultBlockBundle.hpp"

World::World(std::shared_ptr<TQueue<WorldEvent>> queue): _queue(std::move(queue)) {
}

World::~World() {
}

void World::generate() {
    int radius = 10;
    Flat3DArray<BlockTemplateBundledID> chunkData(CHUNK_WIDTH, CHUNK_HEIGHT, CHUNK_WIDTH);
    for (auto x = 0; x < CHUNK_WIDTH; x++) {
        for (auto y = 0; y < CHUNK_HEIGHT / 10; y++) {
            for (auto z = 0; z < CHUNK_WIDTH; z++) {
                if (y == CHUNK_HEIGHT / 10 - 1) {
                    chunkData.set(x, y, z, BlockTemplateBundledID(DEFAULT_BUNDLE_ID, 2));
                } else if (y < CHUNK_HEIGHT / 10 - 5) {
                    chunkData.set(x, y, z, BlockTemplateBundledID(DEFAULT_BUNDLE_ID, 3));
                } else {
                    chunkData.set(x, y, z, BlockTemplateBundledID(DEFAULT_BUNDLE_ID, 1));
                }
            }
        }
    }
    for (int z = 0; z < radius; z++) {
        for (int x = 0; x < radius; x++) {
            Chunk chunk = {
                    glm::vec3(x, 0, z),
                    chunkData,
            };
            _queue->push(chunk);
        }
    }
}
