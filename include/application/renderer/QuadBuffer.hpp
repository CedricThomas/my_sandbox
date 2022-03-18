//
// Created by arzad on 15/03/2022.
//

#ifndef APP_QUADBUFFER_HPP
#define APP_QUADBUFFER_HPP

#include <cstddef>
#include "Quad.hpp"

#define MAX_QUAD_BUFFER_SIZE 10000

class QuadBuffer {
public:
    explicit QuadBuffer(size_t size = MAX_QUAD_BUFFER_SIZE);

    void push(const Quad &quad);

    float *getVertices() const;

    unsigned int *getIndices() const;

    size_t getSize() const;

    size_t getCurrentIndex() const;

    bool isFull() const;

private:
    size_t _size;
    size_t _currentIndex;
    float *_vertices;
    unsigned int *_indices;
};


#endif //APP_QUADBUFFER_HPP
