//
// Created by arzad on 17/01/2022.
//

#ifndef APP_RENDERER_HPP
#define APP_RENDERER_HPP


#include "application/ARenderer.hpp"
#include "application/tools/Shader.hpp"
#include "application/tools/Camera.hpp"
#include "application/tools/RenderingTracker.hpp"
#include "world/World.hpp"
#include "QuadBuffer.hpp"

class Renderer: public ARenderer {
public:
    explicit Renderer(std::shared_ptr<TQueue<WorldUpdate>> queue);

    void onInit(const Application &application) override;

    void onInput(const Application &application) override;

    void onRender(const Application &application) override;

    void onCleanup(const Application &application) override;

    void onMouse(const Application &application, double xpos, double ypos) override;

    void onScroll(const Application &application, double xoffset, double yoffset) override;

    GLuint _vao;
    GLuint _vbo;
    GLuint _ebo{};
    GLuint _textureAtlas;
    Shader _shader;
    Camera _camera;
    QuadBuffer _quadBuffer;
    std::shared_ptr<TQueue<WorldUpdate>> _queue;

    // Application resources
    const RenderingTracker *_tracker;
    GLFWwindow *_window;
};


#endif //APP_RENDERER_HPP
