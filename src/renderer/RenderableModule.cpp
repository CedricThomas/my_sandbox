//
// Created by arzad on 16/01/2022.
//

#include "renderer/RenderableModule.hpp"
#include "spdlog/spdlog.h"

#include <utility>

RenderableModule::RenderableModule(std::string name) : _name(std::move(name)) {}

void RenderableModule::onInit(const Provider &provider) {
    spdlog::debug("[{}] Initialization...", getName());
}

void RenderableModule::onInput(const Provider &provider) {}

void RenderableModule::onRender(const Provider &provider) {}

void RenderableModule::onMouse(const Provider &provider, double xpos, double ypos) {}

void RenderableModule::onScroll(const Provider &provider, double xoffset, double yoffset) {}

void RenderableModule::onCleanup(const Provider &provider) {
    spdlog::debug("[{}] Cleaning...", getName());
}

const std::string &RenderableModule::getName() const {
    return _name;
}
