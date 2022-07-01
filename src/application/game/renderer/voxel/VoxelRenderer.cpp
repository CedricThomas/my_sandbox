//
// Created by arzad on 17/01/2022.
//

#include <utility>
#include "lib/graphics/glad.h"
#include "GLFW/glfw3.h"
#include "glm/gtc/matrix_transform.hpp"
#include "lib/graphics/stb_image.h"
#include "application/Application.hpp"
#include "application/game/renderer/voxel/VoxelRenderer.hpp"
#include "application/game/renderer/voxel/VoxelRenderer.hpp"
#include "application/game/renderer/voxel/containers/Vertex.hpp"
#include "application/game/renderer/voxel/Mesher.hpp"
#include "application/game/AGame.hpp"
#include "lib/resources/ResourcesFinder.hpp"
#include "application/game/texture/TextureAtlas.hpp"
#include "bundling/BundleAtlas.hpp"

VoxelRenderer::VoxelRenderer(
        std::shared_ptr<QuadsMap> _quadsMap,
        std::shared_ptr<TextureAtlas> textureAtlas
) : ARenderer("VoxelRenderer"),
    _vao(0),
    _vbo(0),
    _ebo(0),
    _textureAtlas(0),
    _shader(),
    _quadsMap(std::move(_quadsMap)),
    _atlas(std::move(textureAtlas)) {
    // build and compile our shader program
    // ------------------------------------
    _shader = Shader(
            ResourcesFinder(SHADERS_FOLDER).append("voxel/voxel.vert").get().path,
            ResourcesFinder(SHADERS_FOLDER).append("voxel/voxel.frag").get().path
    );

    // generate and bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);

    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * MAX_VERTEXES_PER_DRAW, nullptr, GL_DYNAMIC_DRAW);

    // position attribute
    glEnableVertexArrayAttrib(_vbo, 0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *) offsetof(Vertex, Position));

    // texture coord attribute
    glEnableVertexArrayAttrib(_vbo, 1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *) offsetof(Vertex, TextureCoords));

    // texture index attribute
    glEnableVertexArrayAttrib(_vbo, 2);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *) offsetof(Vertex, TextureIndex));

    // pre-allocate and load the index buffer
    auto indices = new unsigned int[MAX_INDEXES_PER_DRAW];
    for (size_t i = 0; (i * 6) < MAX_INDEXES_PER_DRAW; i++) {
        indices[i * 6 + 0] = i * 4 + 0;
        indices[i * 6 + 1] = i * 4 + 1;
        indices[i * 6 + 2] = i * 4 + 2;
        indices[i * 6 + 3] = i * 4 + 2;
        indices[i * 6 + 4] = i * 4 + 3;
        indices[i * 6 + 5] = i * 4 + 0;
    }
    glGenBuffers(1, &_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, MAX_INDEXES_PER_DRAW * sizeof(unsigned int), indices, GL_STATIC_DRAW);
    delete[] indices;

    // texture atlas
    // ---------
    glGenTextures(1, &_textureAtlas);
    glBindTexture(GL_TEXTURE_2D, _textureAtlas);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    GL_REPEAT);    // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // import texture atlas
    // ------------------------
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _atlas->getAtlasWidth(), _atlas->getAtlasHeight(), 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, _atlas->getAtlas());
    glGenerateMipmap(GL_TEXTURE_2D);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    _shader.useProgram(); // don't forget to activate/use the shader before setting uniforms!
    _shader.setInt("texture", 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void VoxelRenderer::render(AGame &game) {
    auto config = game.getConfig();

    // bind Texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _textureAtlas);

    // activate shader
    _shader.useProgram();

    // create transformations
    glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float) config.width / (float) config.height, 0.1f, 100.0f);
    // pass transformation matrices to the shader
    _shader.setMat4("projection",
                    projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
    _shader.setMat4("view", game.getCamera().getViewMatrix());

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    for (auto &chunk: *_quadsMap) {
        auto position = chunk.first;
        glBufferSubData(GL_ARRAY_BUFFER, 0, (ssize_t) (*_quadsMap)[position].getSize(),
                        (*_quadsMap)[position].getVertices());

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(position.x * CHUNK_GAP, 0, position.y * CHUNK_GAP));
        _shader.setMat4("model", model);

        glDrawElements(GL_TRIANGLES, (GLsizei) chunk.second.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
    }

    glBindVertexArray(0);
}

VoxelRenderer::~VoxelRenderer() {
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);
    glDeleteBuffers(1, &_ebo);
    _shader.deleteProgram();
}
