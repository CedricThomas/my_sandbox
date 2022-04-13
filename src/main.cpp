#include "spdlog/spdlog.h"
#include "application/Application.hpp"
#include "application/renderer/Renderer.hpp"
#include "world/World.hpp"
#include "lib/Pool.hpp"
#include "lib/containers/TQueue.hpp"
#include "lib/resources/ResourcesFinder.hpp"
#include "bundling/DefaultBlockBundle.hpp"
#include "bundling/BundleAtlas.hpp"
#include "application/texture/TextureAtlas.hpp"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const char *RESOURCES_FOLDER = "../resources";

static void configure() {
    auto &bundleAtlas = BundleAtlas::getInstance();
    auto &textureAtlas = TextureAtlas::getInstance();
    auto &application = Application::getInstance();

    ResourcesFinder::root(RESOURCES_FOLDER);
    bundleAtlas.registerBundle(DEFAULT_BUNDLE);
    textureAtlas.loadBundleBlockTextures(DEFAULT_BUNDLE);
    textureAtlas.generateAtlas();
    application.configure({
                                  SCR_WIDTH,
                                  SCR_HEIGHT,
                                  "Application",
                          });
}

static void start() {
    auto &application = Application::getInstance();
    auto queue = std::make_shared<TQueue<WorldEvent>>();
    Pool pool(1, 2);

    application.registerRenderer(std::make_unique<Renderer>(queue));
    pool.addJob([&]() {
        World world(queue);
        world.generate();
    });
    application.start();
    pool.shutdown();
}


int main() {
    spdlog::set_level(spdlog::level::debug); // Set global log level to debug
    configure();
//    start();
    return 0;

}
