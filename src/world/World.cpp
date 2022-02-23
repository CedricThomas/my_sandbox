//
// Created by arzad on 23/02/2022.
//

#include <iostream>
#include "world/World.hpp"

void World::update(int value) {
    std::cout << "World::update(int value)" << std::endl;
}

void World::update(float value) {
    std::cout << "World::update(float value)" << std::endl;
}
