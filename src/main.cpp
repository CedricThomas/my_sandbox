#include "spdlog/spdlog.h"
#include "application/Application.hpp"
#include "application/renderer//Renderer.hpp"
#include "server/Server.hpp"
#include "world/World.hpp"
#include "lib/Pool.hpp"
#include "lib/containers/Flat3DArray.hpp"
#include "lib/containers/TQueue.hpp"
#include "application/renderer/Vertex.hpp"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void rendering() {
    auto &renderer = Application::getInstance();

    renderer.configure({
                               SCR_WIDTH,
                               SCR_HEIGHT,
                               "Application",
                               "../resources",
                       });
    renderer.registerRenderer(std::make_unique<Renderer>());
    renderer.start();
}

void world_server() {
    auto queue = std::make_shared<TQueue<Flat3DArray<short>>>();

    auto &renderer = Application::getInstance();
    renderer.configure({
                               SCR_WIDTH,
                               SCR_HEIGHT,
                               "Application",
                               "../resources",
                       });
    renderer.registerRenderer(std::make_unique<Renderer>());

    Pool pool(1, 2);

    pool.addJob([&]() {
        World world(queue);
        world.generate();
        world.generate();
        world.generate();
    });
    pool.addJob([&]() {
        while (!pool.isStopping()) {
            auto data = queue->pop();
            if (data.has_value()) {
                std::cout << "received data" << std::endl;
            }
        }
    });
    renderer.start();
    pool.shutdown();
}

void pool() {
    Pool pool(1, 2);

    pool.addJob([&pool]() {
        spdlog::info("Job 1");
        std::this_thread::sleep_for(std::chrono::seconds(10));
    });
    pool.addJob([&pool]() {
        spdlog::info("Job 2");
        std::this_thread::sleep_for(std::chrono::seconds(5));
    });
    pool.addJob([&pool]() {
        spdlog::info("Job 3");
        std::this_thread::sleep_for(std::chrono::seconds(4));
    });
    pool.shutdown();
}
void zip() {
    short data[] = {
            500, 1,
            500, 2,
    };
    auto array = Flat3DArray<short>::unzip(data, 10, 10, 10);
    std::cout << array.getData()[499] << std::endl;
    std::cout << array.getData()[999] << std::endl;
}

int main()
{
    spdlog::set_level(spdlog::level::debug); // Set global log level to debug
    world_server();
//    rendering();
//    pool();
//    zip();
    return 0;

}
