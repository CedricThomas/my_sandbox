//
// Created by arzad on 26/04/2022.
//
#include "application/game/AGame.hpp"
#include "application/game/renderer/voxel/Mesher.hpp"

AGame::AGame(std::shared_ptr<Application> application)
        : _application(std::move(application)),
          _tracker(),
          _camera(glm::vec3(CHUNK_GAP / 2.0f, (float)CHUNK_HEIGHT * (float)VERTEX_GAP / 10.0f, CHUNK_GAP / 2.0f)) {}

const Camera &AGame::getCamera() const {
    return _camera;
}

const Application::ApplicationConfig &AGame::getConfig() {
    return _application->getConfig();
}

GLFWwindow *AGame::getWindow() {
    return _application->getWindow();
}

const RenderingTracker &AGame::getTracker() {
    return _tracker;
}

void AGame::onRender() {
    _tracker.trackFrameTime(static_cast<float>(glfwGetTime()));
}

void AGame::onMouseMove(double xpos, double ypos) {
    _tracker.trackMousePosition(static_cast<float>(xpos), static_cast<float>(ypos));
}
