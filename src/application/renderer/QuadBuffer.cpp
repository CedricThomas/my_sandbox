//
// Created by arzad on 15/03/2022.
//

#include <cstring>
#include <stdexcept>
#include "application/renderer/QuadBuffer.hpp"

float *QuadBuffer::getVertices() const {
    return _vertices;
}

unsigned int *QuadBuffer::getIndices() const {
    return _indices;
}

QuadBuffer::QuadBuffer(size_t size)
        : _size(size),
          _currentIndex(0),
          _vertices(new float[size * 4]),
          _indices(new unsigned int[size * 6]) {}

void QuadBuffer::push(const Quad &quad) {
    if (_currentIndex >= _size) {
        throw std::out_of_range("QuadBuffer is full");
    }
    std::memcpy(_vertices + (_currentIndex * sizeof(Quad)), &quad, sizeof(Quad));
    _indices[_currentIndex * 6] = _currentIndex * 4;
    _indices[_currentIndex * 6 + 1] = _currentIndex * 4 + 1;
    _indices[_currentIndex * 6 + 2] = _currentIndex * 4 + 2;
    _indices[_currentIndex * 6 + 3] = _currentIndex * 4 + 2;
    _indices[_currentIndex * 6 + 4] = _currentIndex * 4 + 3;
    _indices[_currentIndex * 6 + 5] = _currentIndex * 4 + 0;
    _currentIndex++;
}

bool QuadBuffer::isFull() const {
    return _size == _currentIndex;
}

size_t QuadBuffer::getSize() const {
    return _size;
}

size_t QuadBuffer::getCurrentIndex() const {
    return _currentIndex;
}
