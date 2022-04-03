//
// Created by arzad on 23/02/2022.
//

#ifndef APP_WORLD_HPP
#define APP_WORLD_HPP

#include <memory>
#include <variant>
#include "lib/interfaces/Observer.hpp"
#include "lib/containers/Flat3DArray.hpp"
#include "lib/containers/TQueue.hpp"
#include "glm/gtx/hash.hpp"
#include "glm/vec3.hpp"

#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 255

struct Chunk {
    glm::vec3 position;
    Flat3DArray<unsigned short> data;
};
struct ChunkRemove {
    glm::vec3 position;
};
using ChunkMap = std::unordered_map<glm::vec3, Chunk, std::hash<glm::vec3>>;

using WorldEvent = std::variant<Chunk, ChunkRemove>;

class World {
public:
    World(std::shared_ptr<TQueue<WorldEvent>>);

    void generate();
    ~World();

private:
    std::shared_ptr<TQueue<WorldEvent>> _queue;
};


#endif //APP_WORLD_HPP
