//
// Created by arzad on 27/03/2022.
//

#ifndef APP_DEFINITIONS_HPP
#define APP_DEFINITIONS_HPP

#include <variant>
#include "lib/containers/Flat3DArray.hpp"
#include "lib/containers/Flat2DArray.hpp"

// Common

using Chunk = Flat3DArray<unsigned short>;

// Renderer

using VertexArray = const float *;

#define MAX_QUADS_PER_DRAW 195840
#define MAX_VERTEXES_PER_DRAW (MAX_QUADS_PER_DRAW * 4)
#define MAX_INDEXES_PER_DRAW (MAX_QUADS_PER_DRAW * 6)

// Mesher

using Mesh = Flat3DArray<unsigned char>;

#define TOP_SIDE (1 << 1)
#define BOTTOM_SIDE (1 << 2)
#define LEFT_SIDE (1 << 3)
#define RIGHT_SIDE (1 << 4)
#define FRONT_SIDE (1 << 5)
#define BACK_SIDE (1 << 6)

#define VERTEX_MIN (-0.1)
#define VERTEX_MAX (0.1)
#define VERTEX_GAP (VERTEX_MAX - VERTEX_MIN)

// World

using WorldEvent = std::variant<Chunk>;

#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 255

#endif //APP_DEFINITIONS_HPP
