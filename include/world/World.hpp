//
// Created by arzad on 23/02/2022.
//

#ifndef APP_WORLD_HPP
#define APP_WORLD_HPP

#include <memory>
#include "lib/interfaces/Observer.hpp"
#include "lib/containers/Flat3DArray.hpp"
#include "lib/containers/TQueue.hpp"

class World {
public:
    World(std::shared_ptr<TQueue<Flat3DArray<short>>>);

    void generate();
    ~World();

private:
    std::shared_ptr<TQueue<Flat3DArray<short>>> _queue;
};


#endif //APP_WORLD_HPP
