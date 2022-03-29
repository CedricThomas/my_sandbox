#include "spdlog/spdlog.h"
#include "application/Application.hpp"
#include "application/renderer/Renderer.hpp"
#include "server/Server.hpp"
#include "world/World.hpp"
#include "lib/Pool.hpp"
#include "lib/containers/TQueue.hpp"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void start() {
    auto queue = std::make_shared<TQueue<WorldEvent>>();

    auto &application = Application::getInstance();
    application.configure({
                               SCR_WIDTH,
                               SCR_HEIGHT,
                               "Application",
                               "../resources",
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
