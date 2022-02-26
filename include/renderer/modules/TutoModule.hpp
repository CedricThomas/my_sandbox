//
// Created by arzad on 17/01/2022.
//

#ifndef APP_TUTOMODULE_HPP
#define APP_TUTOMODULE_HPP


#include "renderer/RenderableModule.hpp"
#include "renderer/tools/Shader.hpp"
#include "renderer/tools/Camera.hpp"

class TutoModule: public RenderableModule {
public:
    TutoModule();

    void onInit(const Provider &provider) override;

    void onInput(const Provider &provider) override;

    void onRender(const Provider &provider) override;

    void onCleanup(const Provider &provider) override;

    void onMouse(const Provider &provider, double xpos, double ypos) override;

    void onScroll(const Provider &provider, double xoffset, double yoffset) override;

    GLuint _vao;
    GLuint _vbo;
    GLuint _texture1;
    GLuint _texture2;
    Shader _shader;
    Camera _camera;
    Renderer *_renderer;
    GLFWwindow *_window;
};


#endif //APP_TUTOMODULE_HPP
