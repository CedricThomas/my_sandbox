#include "spdlog/spdlog.h"
#include "application/Application.hpp"
#include "application/renderer/Renderer.hpp"
#include "world/World.hpp"
#include "lib/Pool.hpp"
#include "lib/containers/TQueue.hpp"
#include "lib/resources/ResourcesFinder.hpp"
#include "bundling/DefaultBlockBundle.hpp"
#include "bundling/BundleAtlas.hpp"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const char *RESOURCES_FOLDER = "../resources";

// TODO send signal to threads to stop them
void start() {
    ResourcesFinder::root(RESOURCES_FOLDER);
    BundleAtlas::getInstance()->registerBundle(DEFAULT_BUNDLE);

    auto queue = std::make_shared<TQueue<WorldEvent>>();

    auto &application = Application::getInstance();
    application.configure({
                               SCR_WIDTH,
                               SCR_HEIGHT,
                               "Application",
                       });
    application.registerRenderer(std::make_unique<Renderer>(queue));

    Pool pool(1, 2);

    pool.addJob([&]() {
        World world(queue);
        world.generate();
    });
    application.start();
    pool.shutdown();
}

int main()
{
    spdlog::set_level(spdlog::level::debug); // Set global log level to debug
    start();
    return 0;

}
