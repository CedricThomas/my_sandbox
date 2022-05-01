//
// Created by arzad on 23/02/2022.
//

#ifndef APP_WORLD_HPP
#define APP_WORLD_HPP

#include <memory>
#include <variant>
#include "lib/interfaces/Observer.hpp"
#include "lib/containers/Flat3DArray.hpp"
#include "lib/containers/concurrentqueue.h"
#include "glm/gtx/hash.hpp"
#include "glm/vec3.hpp"
#include "world/blocks/BlockTemplate.hpp"
#include "bundling/BundleAtlas.hpp"
#include "bundling/Bundle.hpp"

#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 255

struct Chunk {
    glm::vec3 position;
    Flat3DArray<BlockTemplateBundledID> data;
};

using LoadChunk = Chunk;
struct UnloadChunk {
    glm::vec3 position;
};
using ChunkMap = std::unordered_map<glm::vec3, Chunk, std::hash<glm::vec3>>;

using WorldEvent = std::variant<LoadChunk, UnloadChunk>;

class World {
public:
    World(std::shared_ptr<moodycamel::ConcurrentQueue<WorldEvent>>, std::shared_ptr<BundleAtlas>);

    void generate();
    ~World();

private:
    std::shared_ptr<moodycamel::ConcurrentQueue<WorldEvent>> _queue;
    std::shared_ptr<BundleAtlas> _bundleAtlas;
};


#endif //APP_WORLD_HPP
