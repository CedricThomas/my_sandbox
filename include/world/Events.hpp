//
// Created by arzad on 01/05/2022.
//

#ifndef WORLD_EVENTS_HPP
#define WORLD_EVENTS_HPP

#include <variant>
#include "glm/vec3.hpp"
#include "bundling/Bundle.hpp"
#include "bundling/BundleAtlas.hpp"
#include "lib/containers/Flat3DArray.hpp"

#define WORLD_EVENT_TOPIC "world-topic"

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

#endif // WORLD_EVENTS_HPP
