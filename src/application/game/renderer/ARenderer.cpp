//
// Created by arzad on 16/01/2022.
//

#include "application/game/renderer/ARenderer.hpp"
#include "spdlog/spdlog.h"

#include <utility>

ARenderer::ARenderer(std::string name) : _name(std::move(name)) {}

const std::string &ARenderer::getName() const {
    return _name;
}
