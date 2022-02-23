//
// Created by arzad on 16/01/2022.
//

#ifndef APP_RENDERER_HPP
#define APP_RENDERER_HPP

#include "lib/glad.h"
#include "GLFW/glfw3.h"
#include "RenderableModule.hpp"
#include "lib/utils/Provider.hpp"

#include <map>
#include <string>
#include <list>
#include <functional>
#include <memory>

class Renderer {
// singleton methods and type definition
public:
    static Renderer &getInstance();

    Renderer(Renderer const &) = delete;

    void operator=(Renderer const &) = delete;

private:
    Renderer();

public:
    struct RendererConfig {
        int width;
        int height;
        std::string title;
        std::string resourcesFolder;
    };

    void configure(const RendererConfig &config);

    void registerModule(std::unique_ptr<RenderableModule> &&module);

    void start();

    const RendererConfig &getConfig() const;

private:
    static void
    debug_callback(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char *message,
                   const void *userParam);

    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
//    void mouse_callback(GLFWwindow *window, double xpos, double ypos);
//    void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

    void init();

    void render();

    void cleanup();

    RendererConfig _config;
    std::list<std::unique_ptr<RenderableModule>> _modules;
    GLFWwindow *_window;
    Provider &_provider;

};


#endif //APP_RENDERER_HPP
