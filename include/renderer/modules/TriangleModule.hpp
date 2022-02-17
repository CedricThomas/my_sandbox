//
// Created by arzad on 17/01/2022.
//

#ifndef APP_TRIANGLEMODULE_HPP
#define APP_TRIANGLEMODULE_HPP


#include "renderer/RenderableModule.hpp"
#include "utils/Shader.hpp"

class TriangleModule: public RenderableModule {
public:
    TriangleModule();

    void onInit(const Provider &provider) override;

    void onInput(const Provider &provider) override;

    void onRender(const Provider &provider) override;

    void onCleanup(const Provider &provider) override;

    GLuint _vao;
    GLuint _vbo;
    GLuint _texture1;
    GLuint _texture2;
    GLuint _ebo;
    Shader _shader;
};


#endif //APP_TRIANGLEMODULE_HPP
