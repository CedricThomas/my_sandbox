//
// Created by arzad on 16/01/2022.
//

#ifndef APP_APPLICATION_HPP
#define APP_APPLICATION_HPP

#include "lib/graphics/glad.h"
#include "GLFW/glfw3.h"

#include <map>
#include <string>
#include <list>
#include <functional>
#include <memory>

class AGame;
class Application {
// singleton methods and type definition
public:
    static std::shared_ptr<Application> getInstance();

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

    void registerGame(std::unique_ptr<AGame> &&game);

    void start();

    const ApplicationConfig &getConfig() const;

    GLFWwindow *getWindow() const;

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
    std::unique_ptr<AGame> _game;
    GLFWwindow *_window;

};


#endif //APP_APPLICATION_HPP
