//
// Created by arzad on 17/01/2022.
//

#ifndef APP_RENDERER_HPP
#define APP_RENDERER_HPP

#include "application/ARenderer.hpp"
#include "application/tools/Shader.hpp"
#include "Camera.hpp"
#include "application/tools/RenderingTracker.hpp"
#include "world/World.hpp"
#include "QuadBuffer.hpp"
#include "Mesher.hpp"

#define MAX_VERTEXES_PER_DRAW (MAX_QUADS_PER_DRAW * 4)
#define MAX_INDEXES_PER_DRAW (MAX_QUADS_PER_DRAW * 6)

class Renderer: public ARenderer {
public:
    explicit Renderer(std::shared_ptr<TQueue<WorldEvent>> queue);

    void onInit(const Application &application) override;

    void onInput(const Application &application) override;

    void onRender(const Application &application) override;

    void onCleanup(const Application &application) override;

    void onMouse(const Application &application, double xpos, double ypos) override;

    void onScroll(const Application &application, double xoffset, double yoffset) override;

    GLuint _vao;
    GLuint _vbo;
    GLuint _ebo;
    GLuint _textureAtlas;
    Shader _shader;
    Camera _camera;
    QuadsMap _quadsMap;
    Mesher _mesher;
    std::shared_ptr<TQueue<WorldEvent>> _queue;

    // Application resources
    const RenderingTracker *_tracker;
    GLFWwindow *_window;
};


#endif //APP_RENDERER_HPP
