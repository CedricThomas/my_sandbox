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

using ChunkUpdate = Flat3DArray<unsigned short>;
using WorldUpdate = std::variant<ChunkUpdate>;

class World {
public:
    World(std::shared_ptr<TQueue<WorldUpdate>>);

    void generate();
    ~World();

private:
    std::shared_ptr<TQueue<WorldUpdate>> _queue;
};


#endif //APP_WORLD_HPP
