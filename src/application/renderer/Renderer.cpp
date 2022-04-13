//
// Created by arzad on 17/01/2022.
//

#include "lib/glad.h"
#include <GLFW/glfw3.h>
#include <utility>
#include "application/renderer/Renderer.hpp"
#include "application/Application.hpp"
#include "lib/stb_image.h"
#include "glm/gtc/matrix_transform.hpp"
#include "application/renderer/containers/Vertex.hpp"
#include "application/renderer/Mesher.hpp"
#include "lib/resources/ResourcesFinder.hpp"

Renderer::Renderer(std::shared_ptr<TQueue<WorldEvent>> queue) : ARenderer("Renderer"),
                                                                 _vao(0),
                                                                 _vbo(0),
                                                                 _ebo(0),
                                                                 _textureAtlas(0),
                                                                 _shader(),
                                                                 _camera(glm::vec3(0.0f, 0.0f, 3.0f)),
                                                                 _quadsMap(),
                                                                _mesher(_quadsMap),
                                                                 _queue(std::move(queue)),
                                                                 _tracker(),
                                                                 _window() {}

void Renderer::onInit(const Application &application) {
    ARenderer::onInit(application);

    // Save the usefull variables from the application
    // ------------------------------------
    _window = application.getWindow();
    _tracker = application.getRenderingTracker();

    // build and compile our shader program
    // ------------------------------------
    _shader = Shader(
            ResourcesFinder(SHADERS_FOLDER).append("voxel.vert").get().path,
            ResourcesFinder(SHADERS_FOLDER).append("voxel.frag").get().path
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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
//    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = stbi_load(ResourcesFinder(TEXTURES_FOLDER).append(BLOCKS_FOLDER).append("stone_bricks.png").get().path.c_str(), &width, &height,
                                    &nrChannels,
                                    0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        spdlog::error("[{}] Error loading texture", this->getName());
    }
    stbi_image_free(data);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    _shader.useProgram(); // don't forget to activate/use the shader before setting uniforms!
    // TODO: implement dynamic texture atlas
//    int texture[1] = {0};
//    _shader.setInts("texture", 1, texture);
    _shader.setInt("texture", 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Renderer::onRender(const Application &application) {
    ARenderer::onRender(application);
    auto config = application.getConfig();

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
    _shader.setMat4("view", _camera.getViewMatrix());

    auto data = _queue->pop();
    if (data.has_value()) {
        if (std::holds_alternative<Chunk>(data.value())) {
            auto chunk = std::get<Chunk>(data.value());
            _mesher.insertChunk(chunk);
            _mesher.generateVertexes();
        }
        if (std::holds_alternative<UnloadChunk>(data.value())) {
            auto chunk = std::get<UnloadChunk>(data.value());
            _mesher.removeChunk(chunk.position);
            _mesher.generateVertexes();
        }
    }

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    for (auto &chunk : _quadsMap) {
        auto position = chunk.first;
        glBufferSubData(GL_ARRAY_BUFFER, 0, (ssize_t) _quadsMap[position].getSize(), _quadsMap[position].getVertices());

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(position.x * CHUNK_GAP, position.y, position.z * CHUNK_GAP));
        _shader.setMat4("model", model);

        glDrawElements(GL_TRIANGLES, (GLsizei) chunk.second.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
    }

    glBindVertexArray(0);
}

void Renderer::onCleanup(const Application &application) {
    ARenderer::onCleanup(application);
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);
    glDeleteBuffers(1, &_ebo);
    _shader.deleteProgram();
}

void Renderer::onMouse(const Application &application, double xpos, double ypos) {
    ARenderer::onMouse(application, xpos, ypos);
    _camera.processMouseMovement(_tracker->getMouseXDelta(), _tracker->getMouseYDelta());
}

void Renderer::onScroll(const Application &application, double xoffset, double yoffset) {
    ARenderer::onScroll(application, xoffset, yoffset);
    _camera.processMouseScroll(static_cast<float>(yoffset));
}

void Renderer::onInput(const Application &application) {
    ARenderer::onInput(application);
    if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(_window, true);

    if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
        _camera.processKeyboard(Camera::Movement::FORWARD, _tracker->getFrameDelta());
    if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
        _camera.processKeyboard(Camera::Movement::BACKWARD, _tracker->getFrameDelta());
    if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
        _camera.processKeyboard(Camera::Movement::LEFT, _tracker->getFrameDelta());
    if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
        _camera.processKeyboard(Camera::Movement::RIGHT, _tracker->getFrameDelta());
}
