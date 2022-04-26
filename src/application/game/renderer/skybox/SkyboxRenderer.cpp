//
// Created by arzad on 14/04/2022.
//

#include <vector>
#include <string>
#include "application/game/renderer/skybox/SkyboxRenderer.hpp"
#include "application/game/AGame.hpp"
#include "lib/resources/ResourcesFinder.hpp"
#include "lib/stb_image.h"
#include "glm/gtc/matrix_transform.hpp"
#include "spdlog/spdlog.h"

SkyboxRenderer::SkyboxRenderer() : ARenderer("SkyboxRenderer") {
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

    // position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // generating textures resources
    glGenTextures(1, &_skyboxTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _skyboxTexture);

    // loading textures
    auto root = ResourcesFinder(TEXTURES_FOLDER).append(MISCS_FOLDER);
    const std::vector<std::string> faces = {
            "right.jpg",
            "left.jpg",
            "top.jpg",
            "bottom.jpg",
            "front.jpg",
            "back.jpg"
    };
    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(
                root.append("skybox").append(faces[i]).get().path.c_str(),
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


    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    _shader.useProgram(); // don't forget to activate/use the shader before setting uniforms!
    _shader.setInt("skybox", 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SkyboxRenderer::render(AGame &game) {
    auto camera = game.getCamera();
    auto config = game.getConfig();

    // draw skybox as last
    glDisable(GL_DEPTH_TEST);
    _shader.useProgram();
    auto view = glm::mat4(glm::mat3(camera.getViewMatrix())); // remove translation from the view matrix
    auto projection = glm::perspective(glm::radians(camera.getZoom()), (float)config.width / (float)config.height, 0.1f, 100.0f);
    _shader.setMat4("view", view);
    _shader.setMat4("projection", projection);
    // skybox cube
    glBindVertexArray(_vao);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _skyboxTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glEnable(GL_DEPTH_TEST);
}

SkyboxRenderer::~SkyboxRenderer() {
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);
    _shader.deleteProgram();
}
