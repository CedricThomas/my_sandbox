//
// Created by arzad on 15/03/2022.
//

#ifndef APP_VERTEX_HPP
#define APP_VERTEX_HPP


#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

struct Vertex {
public:
    Vertex(const glm::vec3 &position, const glm::vec2 &texCoords, float textureIndex);

    glm::vec3 position;
    glm::vec2 texCoords;
    float textureIndex;
};


#endif //APP_VERTEX_HPP
