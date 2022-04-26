//
// Created by arzad on 16/01/2022.
//

#ifndef APP_APPLICATION_HPP
#define APP_APPLICATION_HPP

#include "lib/glad.h"
#include "GLFW/glfw3.h"
#include "ARenderer.hpp"
#include "application/renderer/RenderingTracker.hpp"

#include <map>
#include <string>
#include <list>
#include <functional>
#include <memory>

class Application {
// singleton methods and type definition
public:
    static Application &getInstance();

    Application(Application const &) = delete;

    void operator=(Application const &) = delete;

private:
    Application();

public:
    struct ApplicationConfig {
        int width;
        int height;
        std::string title;
    };

    void configure(const ApplicationConfig &config);

    void registerRenderer(std::unique_ptr<ARenderer> &&renderer);

    void start();

    const ApplicationConfig &getConfig() const;

    GLFWwindow *getWindow() const;

    const RenderingTracker *getRenderingTracker() const;

private:
    static void
    debug_callback(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char *message,
                   const void *userParam);

    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    static void mouse_callback(GLFWwindow *window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

    void init();

    void render();

    void cleanup();

    ApplicationConfig _config;
    RenderingTracker _tracker;
    std::list<std::unique_ptr<ARenderer>> _renderers;
    GLFWwindow *_window;

};


#endif //APP_APPLICATION_HPP
