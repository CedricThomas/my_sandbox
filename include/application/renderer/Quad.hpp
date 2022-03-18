//
// Created by arzad on 15/03/2022.
//

#ifndef APP_QUAD_HPP
#define APP_QUAD_HPP

#include "Vertex.hpp"

struct Quad {
    Quad(const Vertex &v1, const Vertex &v2, const Vertex &v3, const Vertex &v4);

    Vertex v1, v2, v3, v4;
};


#endif //APP_QUAD_HPP
