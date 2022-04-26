//
// Created by arzad on 14/04/2022.
//

#include <vector>
#include <string>
#include "application/game/renderer/skybox/SkyboxRenderer.hpp"
#include "lib/resources/ResourcesFinder.hpp"
#include "lib/stb_image.h"

SkyboxRenderer::SkyboxRenderer() : ARenderer("SkyboxRenderer") {}

void SkyboxRenderer::onInit(const Application &application) {
    ARenderer::onInit(application);
    float skyboxVertices[] = {
            // positions
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f,  1.0f
    };

    // build and compile our shader program
    // ------------------------------------
    _shader = Shader(
            ResourcesFinder(SHADERS_FOLDER).append("skybox/skybox.vert").get().path,
            ResourcesFinder(SHADERS_FOLDER).append("skybox/skybox.frag").get().path
    );

    // generate and bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);


    // generating textures resources
    glGenTextures(1, &_skyboxTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _skyboxTexture);

    // loading textures
    auto root = ResourcesFinder(MISCS_FOLDER);
    const std::vector<std::string> faces = {
            "right.png",
            "left.png",
            "top.png",
            "bottom.png",
            "front.png",
            "back.png"
    };
    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(
                root.append(faces[i]).get().path.c_str(),
                &width,
                &height,
                &nrChannels,
                0
        );
        glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0,
                GL_RGB,
                width,
                height,
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                data
        );
        stbi_image_free(data);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

}

void SkyboxRenderer::onRender(const Application &application) {
    ARenderer::onRender(application);
    // TODO move camera at game level to implement skybox
}

void SkyboxRenderer::onCleanup(const Application &application) {
    ARenderer::onCleanup(application);
}
