//
// Created by arzad on 16/01/2022.
//
#include "renderer/Renderer.hpp"
#include "renderer/RendererException.hpp"
#include "spdlog/spdlog.h"
#include "renderer/modules/TriangleModule.hpp"
#include "utils/ResourcesManager.hpp"

Renderer &Renderer::getInstance() {
    static Renderer instance;
    return instance;
}

Renderer::Renderer() :
        _config({
                        800,
                        600,
                        "Window",
                        "resources",
                }),
        _modules(),
        _window(nullptr),
        _provider() {

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void Renderer::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    spdlog::debug("Resizing to {} x {}", width, height);
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
void Renderer::init() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    _window = glfwCreateWindow(_config.width, _config.height, _config.title.c_str(), NULL, NULL);
    if (_window == nullptr) {
        glfwTerminate();
        throw RendererException("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(_window);
    glfwSetFramebufferSizeCallback(_window, Renderer::framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw RendererException("Failed to initialize GLAD");
    }

    // registering resources in the utils
    // ---------------------------------------
    _provider.share<GLFWwindow>("window", _window);
    _provider.store<ResourcesManager>("resourcesManager", new ResourcesManager(_config.resourcesFolder));

    // custom init
    // ---------------------------------------
    for (auto &module :  _modules)
        module->onInit(_provider);
}

void Renderer::render() {
    // render loop
    // -----------
    while (!glfwWindowShouldClose(_window)) {
        // input
        // -----
        for (auto &module :  _modules)
            module->onInput(_provider);

        // render
        // ------
        for (auto &module :  _modules)
            module->onRender(_provider);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(_window);
        glfwPollEvents();
    }
}

void Renderer::cleanup() {
    // custom cleanup
    // ------------------------------------------------------------------
    for(auto moduleIt = _modules.rbegin(); moduleIt != _modules.rend(); moduleIt++ )
        (*moduleIt)->onCleanup(_provider);

    // glfw: terminate, clearing all previously allocated GLFW resources
    // ------------------------------------------------------------------
    glfwTerminate();
}

void Renderer::start() {
    init();
    render();
    cleanup();
}

void Renderer::configure(const Renderer::RendererConfig &config) {
    _config = config;
}

void Renderer::registerModule(std::unique_ptr<RenderableModule> &&module) {
    spdlog::debug("[{}] Registering", module->getName());
    _modules.push_back(std::move(module));
}
