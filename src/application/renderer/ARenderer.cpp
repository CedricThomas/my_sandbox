//
// Created by arzad on 16/01/2022.
//

#include "application/ARenderer.hpp"
#include "spdlog/spdlog.h"

#include <utility>

ARenderer::ARenderer(std::string name) : _name(std::move(name)) {}

void ARenderer::onInit(const Application &application) {
    spdlog::debug("[{}] Initialization...", getName());
}

void ARenderer::onInput(const Application &application) {}

void ARenderer::onRender(const Application &application) {}

void ARenderer::onMouse(const Application &application, double xpos, double ypos) {}

void ARenderer::onScroll(const Application &application, double xoffset, double yoffset) {}

void ARenderer::onCleanup(const Application &application) {
    spdlog::debug("[{}] Cleaning...", getName());
}

const std::string &ARenderer::getName() const {
    return _name;
}
