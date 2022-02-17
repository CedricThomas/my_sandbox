
#include "spdlog/spdlog.h"
#include "renderer/Renderer.hpp"
#include "renderer/modules/TriangleModule.hpp"
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
    renderer.registerModule(std::make_unique<TriangleModule>());
    renderer.start();
    return 0;
}
