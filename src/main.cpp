#include "spdlog/spdlog.h"
#include "application/Application.hpp"
#include "application/renderer//Renderer.hpp"
#include "server/Server.hpp"
#include "world/World.hpp"
#include "lib/Pool.hpp"
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
    Server server;
    World world;

    server.Observable<int>::addObserver((Observer<int> *)&world);
    server.Observable<float>::addObserver((Observer<float> *)&world);
    server.start();
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

int main()
{
    spdlog::set_level(spdlog::level::debug); // Set global log level to debug
    rendering();
//    pool();
    return 0;

}
