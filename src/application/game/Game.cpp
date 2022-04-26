//
// Created by arzad on 20/04/2022.
//

#include "application/game/Game.hpp"
#include "application/game/renderer/voxel/VoxelRenderer.hpp"

Game::Game(
        const std::shared_ptr<Application> &application,
        const std::shared_ptr<TQueue<WorldEvent>> &worldEventQueue,
        const std::shared_ptr<BundleAtlas> &bundleAtlas,
        const std::shared_ptr<TextureAtlas> &textureAtlas
) :
AGame(application),
_quadsMap(new QuadsMap()),
_textureAtlas(textureAtlas),
_bundleAtlas(bundleAtlas),
_eventQueue(worldEventQueue),
_mesher(bundleAtlas, textureAtlas, _quadsMap),
_renderers() {}

void Game::onInit() {
    _renderers.emplace_back(std::make_unique<VoxelRenderer>(_quadsMap, _textureAtlas));

}

void Game::onInput() {
    auto window = _application->getWindow();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        _camera.processKeyboard(Camera::Movement::FORWARD, _tracker.getFrameDelta());
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        _camera.processKeyboard(Camera::Movement::BACKWARD, _tracker.getFrameDelta());
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        _camera.processKeyboard(Camera::Movement::LEFT, _tracker.getFrameDelta());
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        _camera.processKeyboard(Camera::Movement::RIGHT, _tracker.getFrameDelta());
}

void Game::onRender() {
    AGame::onRender();
    // input from queue
    auto data = _eventQueue->pop();
    if (data.has_value()) {
        if (std::holds_alternative<Chunk>(data.value())) {
            auto chunk = std::get<Chunk>(data.value());
            _mesher.insertChunk(chunk);
            _mesher.meshUpdates();
        }
        if (std::holds_alternative<UnloadChunk>(data.value())) {
            auto chunk = std::get<UnloadChunk>(data.value());
            _mesher.removeChunk(chunk.position);
            _mesher.meshUpdates();
        }
    }
    for (auto &renderer : _renderers) {
        renderer->render(*this);
    }
    _tracker.trackFrameTime(static_cast<float>(glfwGetTime()));
}

void Game::onCleanup() {

}

void Game::onMouseMove(double xpos, double ypos) {
    AGame::onMouseMove(xpos, ypos);
    _camera.processMouseMovement(_tracker.getMouseXDelta(), _tracker.getMouseYDelta());
}

void Game::onScroll(double xoffset, double yoffset) {
    _camera.processMouseScroll(static_cast<float>(yoffset));
}
