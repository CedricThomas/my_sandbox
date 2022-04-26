//
// Created by arzad on 14/04/2022.
//

#ifndef APP_SKYBOXRENDERER_HPP
#define APP_SKYBOXRENDERER_HPP


#include "lib/glad.h"
#include "application/game/renderer/ARenderer.hpp"
#include "application/game/renderer/Shader.hpp"

class SkyboxRenderer: public ARenderer {
public:
    SkyboxRenderer();

    virtual ~SkyboxRenderer();

    void render(AGame &game) override;

private:
    GLuint _vao;
    GLuint _vbo;
    GLuint _skyboxTexture;
    Shader _shader;
};


#endif //APP_SKYBOXRENDERER_HPP
