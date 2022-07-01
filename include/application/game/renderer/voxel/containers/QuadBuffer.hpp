//
// Created by arzad on 15/03/2022.
//

#ifndef APP_QUADBUFFER_HPP
#define APP_QUADBUFFER_HPP

#include <cstddef>
#include <vector>
#include <unordered_map>
#include "glm/gtx/hash.hpp"
#include "Quad.hpp"

#define MAX_QUADS_PER_DRAW 195840

using VertexArray = const float *;

class QuadBuffer {
public:
    explicit QuadBuffer(size_t capacity = MAX_QUADS_PER_DRAW);

    void emplace_back(const Quad &quad);

    void clear();

    VertexArray getVertices() const;

    size_t getSize();

    size_t getIndicesCount();

private:
    size_t _capacity;
    std::vector<Quad> _quads;
};

using QuadsMap = std::unordered_map<glm::vec2, QuadBuffer, std::hash<glm::vec2>>;

#endif //APP_QUADBUFFER_HPP
