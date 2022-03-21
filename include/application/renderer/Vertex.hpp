//
// Created by arzad on 15/03/2022.
//

#ifndef APP_VERTEX_HPP
#define APP_VERTEX_HPP


#include <ostream>
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

struct Vertex {
public:
    Vertex(const glm::vec3 &Position, const glm::vec2 &TextureCoords, float TextureIndex);

    friend std::ostream &operator<<(std::ostream &os, const Vertex &vertex);

    glm::vec3 Position;
    glm::vec2 TextureCoords;
    float TextureIndex;
};


#endif //APP_VERTEX_HPP
