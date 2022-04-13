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
    BlockTemplateID max_block = CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_HEIGHT;
    BlockTemplateID number = CHUNK_WIDTH * CHUNK_WIDTH * 125;
    BlockTemplateID data[] = {
            number, 1,
            static_cast<BlockTemplateID>((max_block - number)), 0,
    };
    int radius = 2;
    for (int z = 0; z < radius; z++) {
        for (int x = 0; x < radius; x++) {
            auto chunkData = Flat3DArray<BlockTemplateID>::unzip(data, CHUNK_WIDTH, CHUNK_HEIGHT, CHUNK_WIDTH);
            Chunk chunk = {
                    glm::vec3(x, 0, z),
                    chunkData,
            };
            _queue->push(chunk);
        }
    }
    while (1) {
        for (int z = 0; z < radius; z++) {
            for (int x = 0; x < radius; x++) {
                UnloadChunk chunkRemove = {
                        glm::vec3(x, 0, z),
                };
                _queue->push(chunkRemove);
                sleep(4);
            }
        }
        for (int z = 0; z < radius; z++) {
            for (int x = 0; x < radius; x++) {
                auto chunkData = Flat3DArray<BlockTemplateID>::unzip(data, CHUNK_WIDTH, CHUNK_HEIGHT, CHUNK_WIDTH);
                Chunk chunk = {
                        glm::vec3(x, 0, z),
                        chunkData,
                };
                _queue->push(chunk);
                sleep(4);
            }
        }
    }
}
