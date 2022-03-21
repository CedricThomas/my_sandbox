//
// Created by arzad on 15/03/2022.
//

#ifndef APP_QUADBUFFER_HPP
#define APP_QUADBUFFER_HPP

#include <cstddef>
#include <vector>
#include "Quad.hpp"

class QuadBuffer {
public:
    explicit QuadBuffer(size_t capacity);

    void emplace_back(const Quad &quad);

    void clear();

    const float *getVertices() const;

    size_t getSize();

    size_t getIndicesCount();

private:
    size_t _capacity;
    std::vector<Quad> _quads;
};


#endif //APP_QUADBUFFER_HPP
