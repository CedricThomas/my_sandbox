//
// Created by arzad on 17/01/2022.
//

#ifndef APP_RENDERER_HPP
#define APP_RENDERER_HPP


#include "application/ARenderer.hpp"
#include "application/tools/Shader.hpp"
#include "application/tools/Camera.hpp"
#include "application/tools/RenderingTracker.hpp"

class Renderer: public ARenderer {
public:
    Renderer();

    void onInit(const Application &application) override;

    void onInput(const Application &application) override;

    void onRender(const Application &application) override;

    void onCleanup(const Application &application) override;

    void onMouse(const Application &application, double xpos, double ypos) override;

    void onScroll(const Application &application, double xoffset, double yoffset) override;

    GLuint _vao;
    GLuint _vbo;
    GLuint _ebo;
    GLuint _texture1;
    GLuint _texture2;
    Shader _shader;
    Camera _camera;

    // Application resources
    const RenderingTracker *_tracker;
    GLFWwindow *_window;
};


#endif //APP_RENDERER_HPP
