//
// Created by arzad on 20/04/2022.
//

#ifndef APP_GAME_HPP
#define APP_GAME_HPP


#include <list>
#include <memory>
#include "application/game/renderer/ARenderer.hpp"
#include "application/game/renderer/RenderingTracker.hpp"
#include "Camera.hpp"
#include "application/game/renderer/voxel/Mesher.hpp"
#include "AGame.hpp"

class Game : public AGame {
public:

    Game(
            const std::shared_ptr<Application> &application,
            std::shared_ptr<moodycamel::ConcurrentQueue<WorldEvent>> worldEventQueue,
            const std::shared_ptr<BundleAtlas> &bundleAtlas,
            const std::shared_ptr<TextureAtlas> &textureAtlas
    );

    void onInit() override;

    void onInput() override;

    void onRender() override;

    void onCleanup() override;

    void onMouseMove(double xpos, double ypos) override;

    void onScroll(double xoffset, double yoffset) override;

private:
    // game config
    std::shared_ptr<BundleAtlas> _bundleAtlas;
    std::shared_ptr<TextureAtlas> _textureAtlas;

    // world structure
    std::shared_ptr<QuadsMap> _quadsMap;
    std::shared_ptr<moodycamel::ConcurrentQueue<WorldEvent>> _eventQueue;
    Mesher _mesher;

    // rendering
    std::list<std::unique_ptr<ARenderer>> _renderers;

};


#endif //APP_GAME_HPP
