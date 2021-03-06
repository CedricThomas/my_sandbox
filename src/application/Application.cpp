//
// Created by arzad on 16/01/2022.
//
#include <sstream>
#include "application/Application.hpp"
#include "application/game/AGame.hpp"
#include "application/ApplicationException.hpp"
#include "spdlog/spdlog.h"

std::shared_ptr<Application> Application::getInstance() {
    static auto instance = std::shared_ptr<Application>(new Application());
    return instance;
}

Application::Application() :
        _config({
                800,
                600,
                "Window",
        }),
        _game(),
        _window(nullptr){

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void Application::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    spdlog::debug("[GLW callback] Resizing to {} x {}", width, height);
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    static auto application = Application::getInstance();
    application->_config.width = width;
    application->_config.height = height;
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse is moved this callback function executes
// ---------------------------------------------------------------------------------------------
void Application::mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    static auto application = Application::getInstance();
    application->_game->onMouseMove(static_cast<float>(xpos), static_cast<float>(ypos));
}

// glfw: whenever the mouse wheel is triggered this callback function executes
// ---------------------------------------------------------------------------------------------
void Application::scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    static auto application = Application::getInstance();
    application->_game->onScroll(xoffset, yoffset);
}

// glfw: whenever a debut log must be show this callback function executes
// ---------------------------------------------------------------------------------------------
void APIENTRY Application::debug_callback(GLenum source,
                                          GLenum type,
                                          unsigned int id,
                                          GLenum severity,
                                          GLsizei length,
                                          const char *message,
                                          const void *userParam) {
    std::stringstream errorStream;

    // ignore non-significant error/warning codes
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

    errorStream << "[GLW callback] Debug (" << id << ") :" << std::endl << message << std::endl;

    switch (source) {
        case GL_DEBUG_SOURCE_API:
            errorStream << "Source: API";
            break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            errorStream << "Source: Window System";
            break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            errorStream << "Source: Shader Compiler";
            break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            errorStream << "Source: Third Party";
            break;
        case GL_DEBUG_SOURCE_APPLICATION:
            errorStream << "Source: Application";
            break;
        case GL_DEBUG_SOURCE_OTHER:
            errorStream << "Source: Other";
            break;
    }
    errorStream << std::endl;

    switch (type) {
        case GL_DEBUG_TYPE_ERROR:
            errorStream << "Type: Error";
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            errorStream << "Type: Deprecated Behaviour";
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            errorStream << "Type: Undefined Behaviour";
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            errorStream << "Type: Portability";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            errorStream << "Type: Performance";
            break;
        case GL_DEBUG_TYPE_MARKER:
            errorStream << "Type: Marker";
            break;
        case GL_DEBUG_TYPE_PUSH_GROUP:
            errorStream << "Type: Push Group";
            break;
        case GL_DEBUG_TYPE_POP_GROUP:
            errorStream << "Type: Pop Group";
            break;
        case GL_DEBUG_TYPE_OTHER:
            errorStream << "Type: Other";
            break;
    }
    errorStream << std::endl;

    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
            errorStream << "Severity: high";
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            errorStream << "Severity: medium";
            break;
        case GL_DEBUG_SEVERITY_LOW:
            errorStream << "Severity: low";
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            errorStream << "Severity: notification";
            break;
    }
    errorStream << std::endl;
    spdlog::error(errorStream.str());
}

void Application::init() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    // glfw window creation
    // --------------------
    _window = glfwCreateWindow(_config.width, _config.height, _config.title.c_str(), NULL, NULL);
    if (_window == nullptr) {
        glfwTerminate();
        throw ApplicationException("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(_window);
    glfwSetFramebufferSizeCallback(_window, Application::framebuffer_size_callback);
    glfwSetCursorPosCallback(_window, mouse_callback);
    glfwSetScrollCallback(_window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw ApplicationException("Failed to initialize GLAD");
    }

    // initialize debug output
    int flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(debug_callback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // custom init
    // ---------------------------------------
    _game->onInit();
}

void Application::render() {
    // render loop
    // -----------
    while (!glfwWindowShouldClose(_window)) {
        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

        // input
        // -----
        _game->onInput();

        // render
        // ------
        _game->onRender();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(_window);
        glfwPollEvents();
    }
}

void Application::cleanup() {
    // custom cleanup
    // ------------------------------------------------------------------
    _game->onCleanup();

    // glfw: terminate, clearing all previously allocated GLFW resources
    // ------------------------------------------------------------------
    glfwTerminate();
}

void Application::start() {
    init();
    render();
    cleanup();
}

void Application::configure(const Application::ApplicationConfig &config) {
    _config = config;
}

const Application::ApplicationConfig &Application::getConfig() const {
    return _config;
}


GLFWwindow *Application::getWindow() const {
    return _window;
}

void Application::registerGame(std::unique_ptr<AGame> &&game) {
    _game = std::move(game);
}
