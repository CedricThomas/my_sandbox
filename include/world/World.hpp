//
// Created by arzad on 23/02/2022.
//

#ifndef APP_WORLD_HPP
#define APP_WORLD_HPP

#include <memory>
#include "lib/broker/Topic.hpp"
#include "protocol/world/Events.hpp"
#include "protocol/game/Events.hpp"
#include "bundling/BundleAtlas.hpp"

#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 255

struct Chunk {
    glm::vec3 position;
    Flat3DArray<BlockTemplateBundledID> data;
};
using ChunkMap = std::unordered_map<glm::vec3, Chunk, std::hash<glm::vec3>>;

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
