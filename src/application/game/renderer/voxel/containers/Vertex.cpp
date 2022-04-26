//
// Created by arzad on 15/03/2022.
//

#include "application/game/renderer/voxel/containers/Vertex.hpp"
#include "glm/gtc/matrix_transform.hpp"

Vertex::Vertex(const glm::vec3 &position, const glm::vec2 &textureCoords, float textureIndex) : Position(position),
                                                                                                TextureCoords(textureCoords),
                                                                                                TextureIndex(textureIndex) {}

void Vertex::translate(const glm::mat4 &translation) const {
    glm::translate(translation, Position);
}
