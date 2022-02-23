
#include "spdlog/spdlog.h"
#include "renderer/Renderer.hpp"
#include "renderer/modules/TutoModule.hpp"
#include "server/Server.hpp"
#include "world/World.hpp"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    spdlog::set_level(spdlog::level::debug); // Set global log level to debug
    auto &renderer = Renderer::getInstance();

    renderer.configure({
        SCR_WIDTH,
        SCR_HEIGHT,
        "Application",
        "../resources",
    });
//    renderer.registerModule(std::make_unique<TutoModule>());
//    renderer.start();

    Server server;
    World world;

    server.Observable<int>::addObserver((Observer<int> *)&world);
    server.Observable<float>::addObserver((Observer<float> *)&world);
    server.start();


    return 0;
}
