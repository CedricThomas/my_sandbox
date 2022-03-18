//
// Created by arzad on 15/03/2022.
//

#include "application/renderer/Vertex.hpp"

Vertex::Vertex(const glm::vec3 &position, const glm::vec2 &texCoords, float textureIndex) : position(position),
                                                                                            texCoords(texCoords),
                                                                                            textureIndex(
                                                                                                    textureIndex) {}
