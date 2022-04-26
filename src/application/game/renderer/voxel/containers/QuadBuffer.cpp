//
// Created by arzad on 15/03/2022.
//

#include <cstring>
#include <stdexcept>
#include "application/game/renderer/voxel//containers/QuadBuffer.hpp"

VertexArray QuadBuffer::getVertices() const {
    return reinterpret_cast<VertexArray>(_quads.data());
}

QuadBuffer::QuadBuffer(size_t capacity)
        : _capacity(capacity),
          _quads() {
    _quads.reserve(capacity);
}

void QuadBuffer::clear() {
    _quads.clear();
}

void QuadBuffer::emplace_back(const Quad &quad) {
    if (_quads.size() >= _capacity) {
        throw std::runtime_error("QuadBuffer is full");
    }
    _quads.emplace_back(quad);
}

size_t QuadBuffer::getSize() {
    return _quads.size() * sizeof(Quad);
}

size_t QuadBuffer::getIndicesCount() {
    return _quads.size() * 6;
}
