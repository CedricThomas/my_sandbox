#include "spdlog/spdlog.h"
#include "application/Application.hpp"
#include "world/World.hpp"
#include "lib/Pool.hpp"
#include "lib/containers/concurrentqueue.h"
#include "lib/resources/ResourcesFinder.hpp"
#include "bundling/DefaultBlockBundle.hpp"
#include "bundling/BundleAtlas.hpp"
#include "application/game/texture/TextureAtlas.hpp"
#include "application/game/Game.hpp"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const char *RESOURCES_FOLDER = "../resources";

static void configure(std::shared_ptr<BundleAtlas> &bundleAtlas, std::shared_ptr<TextureAtlas> &textureAtlas) {
    auto application = Application::getInstance();

    ResourcesFinder::root(RESOURCES_FOLDER);
    bundleAtlas->registerBundle(DEFAULT_BUNDLE);
    textureAtlas->loadBundleBlockTextures(DEFAULT_BUNDLE);
    textureAtlas->generateAtlas();
    application->configure({
                                  SCR_WIDTH,
                                  SCR_HEIGHT,
                                  "Application",
                          });
}

static void start(std::shared_ptr<BundleAtlas> &bundleAtlas, std::shared_ptr<TextureAtlas> &textureAtlas) {
    auto application = Application::getInstance();
    auto queue = std::make_shared<moodycamel::ConcurrentQueue<WorldEvent>>();
    Pool pool(1, 2);

    application->registerGame(std::make_unique<Game>(application, queue, bundleAtlas, textureAtlas));
    pool.addJob([&]() {
        World world(queue, bundleAtlas);
        world.generate();
    });
    application->start();
    pool.shutdown();
}


int main() {
    spdlog::set_level(spdlog::level::debug); // Set global log level to debug
    auto bundleAtlas =std::make_shared<BundleAtlas>();
    auto textureAtlas = std::make_shared<TextureAtlas>();
    configure(bundleAtlas, textureAtlas);
    start(bundleAtlas, textureAtlas);
    return 0;

}
