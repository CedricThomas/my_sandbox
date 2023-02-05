//
// Created by arzad on 20/04/2022.
//

#include "application/game/Game.hpp"
#include "application/game/renderer/voxel/VoxelRenderer.hpp"
#include "application/game/renderer/skybox/SkyboxRenderer.hpp"
#include "protocol/world/Types.hpp"
#include "protocol/world/LoadChunk.hpp"
#include "protocol/world/UnloadChunk.hpp"
#include "protocol/game/Move.hpp"
#include "protocol/game/Join.hpp"

Game::Game(
        const std::shared_ptr<Application> &application,
        std::shared_ptr<ASubscription<WorldEvent, GameEvent>> worldEventSubscription,
        const std::shared_ptr<BundleAtlas> &bundleAtlas,
        const std::shared_ptr<TextureAtlas> &textureAtlas
) :
AGame(application),
_quadsMap(new QuadsMap()),
_textureAtlas(textureAtlas),
_bundleAtlas(bundleAtlas),
_worldEventSubscription(worldEventSubscription),
_mesher(bundleAtlas, textureAtlas, _quadsMap),
_renderers() {
    _worldEventSubscription->pushToTopic(std::make_shared<Join>(_camera.getPosition()));
}

void Game::onInit() {
    _renderers.emplace_back(std::make_unique<SkyboxRenderer>());
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
    _worldEventSubscription->pushToTopic(std::make_shared<Move>(_camera.getPosition()));
}

void Game::onRender() {
    AGame::onRender();

    WorldEvent worldEvent;
    LoadChunk *loadChunk;
    UnloadChunk *unloadChunk;
    auto hasData = _worldEventSubscription->tryPull(worldEvent);
    if (hasData) {
        switch (static_cast<WorldEventType>(worldEvent->getType())) {
            case WorldEventType::LOAD_CHUNK:
                loadChunk = dynamic_cast<LoadChunk *>(worldEvent.get());
                _mesher.insertChunk(Chunk{
                        loadChunk->position,
                        loadChunk->data,
                });
                _mesher.meshUpdates();
                spdlog::info("MOVED TO ({},{})", loadChunk->position.x, loadChunk->position.y);
                break;
            case WorldEventType::UNLOAD_CHUNK:
                unloadChunk = dynamic_cast<UnloadChunk *>(worldEvent.get());
                _mesher.removeChunk(unloadChunk->position);
                _mesher.meshUpdates();
                break;
            default:
                break;
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
