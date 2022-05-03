//
// Created by arzad on 01/05/2022.
//
#define ENET_IMPLEMENTATION
#include "lib/enet.h"

#include <stdexcept>
#include "server/Enet.hpp"

void ENET::init() {
    if (enet_initialize() != 0) {
        throw std::runtime_error("An error occurred while initializing ENet.");
    }
    atexit(enet_deinitialize);
}
