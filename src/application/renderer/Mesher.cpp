//
// Created by arzad on 23/03/2022.
//

#include "application/renderer/Mesher.hpp"
#include "spdlog/spdlog.h"

Mesh Mesher::meshChunk(const Chunk &chunk) {
    Mesh mesh(chunk.getX(), chunk.getY(), chunk.getZ());
    for (int y = 0; y < CHUNK_HEIGHT; y++) {
        for (int x = 0; x < CHUNK_WIDTH; x++) {
            for (int z = 0; z < CHUNK_WIDTH; z++) {
                // if the current block is empty skip it
                if (chunk.get(x, y, z) == 0)
                    continue;
                unsigned char block = 0;
                // if the adjacent block is not empty, doesnt add the face to the mesh
                // if the adjacent block is empty, add the face to the mesh
                // if the adjacent block is outside the chunk, add the face to the mesh
                if (y == 0 || chunk.get(x, y - 1, z) == 0)
                    block |= BOTTOM_SIDE;
                if (y == CHUNK_HEIGHT - 1 || chunk.get(x, y + 1, z) == 0)
                    block |= TOP_SIDE;
                if (x == 0 || chunk.get(x - 1, y, z) == 0)
                    block |= LEFT_SIDE;
                if (x == CHUNK_WIDTH - 1 || chunk.get(x + 1, y, z) == 0)
                    block |= RIGHT_SIDE;
                if (z == CHUNK_WIDTH - 1 || chunk.get(x, y, z + 1) == 0)
                    block |= FRONT_SIDE;
                if (z == 0 || chunk.get(x, y, z - 1) == 0)
                    block |= BACK_SIDE;
                mesh.set(x, y, z, block);
            }
        }
    }
    return mesh;
}

void Mesher::generateQuadBuffer(QuadBuffer &quads, const Mesh &mesh) {
    quads.clear();
    for (int y = 0; y < CHUNK_HEIGHT; y++) {
        for (int x = 0; x < CHUNK_WIDTH; x++) {
            for (int z = 0; z < CHUNK_WIDTH; z++) {
                unsigned char block = mesh.get(x, y, z);
                if (block == 0)
                    continue;
                if (block & BACK_SIDE) {
                    quads.emplace_back(Quad(
                            Vertex(glm::vec3((x * VERTEX_GAP) + VERTEX_MIN, (y * VERTEX_GAP) + VERTEX_MIN, (z * VERTEX_GAP) + VERTEX_MIN), glm::vec2(0.0f, 0.0f), 0.0f),
                            Vertex(glm::vec3((x * VERTEX_GAP) + VERTEX_MAX, (y * VERTEX_GAP) + VERTEX_MIN, (z * VERTEX_GAP) + VERTEX_MIN), glm::vec2(1.0f, 0.0f), 0.0f),
                            Vertex(glm::vec3((x * VERTEX_GAP) + VERTEX_MAX, (y * VERTEX_GAP) + VERTEX_MAX, (z * VERTEX_GAP) + VERTEX_MIN), glm::vec2(1.0f, 1.0f), 0.0f),
                            Vertex(glm::vec3((x * VERTEX_GAP) + VERTEX_MIN, (y * VERTEX_GAP) + VERTEX_MAX, (z * VERTEX_GAP) + VERTEX_MIN), glm::vec2(0.0f, 1.0f), 0.0f)
                    ));
                }
                if (block & FRONT_SIDE) {
                    quads.emplace_back(Quad(
                            Vertex(glm::vec3((x * VERTEX_GAP) + VERTEX_MIN, (y * VERTEX_GAP) + VERTEX_MIN, (z * VERTEX_GAP) + VERTEX_MAX), glm::vec2(0.0f, 0.0f), 0.0f),
                            Vertex(glm::vec3((x * VERTEX_GAP) + VERTEX_MAX, (y * VERTEX_GAP) + VERTEX_MIN, (z * VERTEX_GAP) + VERTEX_MAX), glm::vec2(1.0f, 0.0f), 0.0f),
                            Vertex(glm::vec3((x * VERTEX_GAP) + VERTEX_MAX, (y * VERTEX_GAP) + VERTEX_MAX, (z * VERTEX_GAP) + VERTEX_MAX), glm::vec2(1.0f, 1.0f), 0.0f),
                            Vertex(glm::vec3((x * VERTEX_GAP) + VERTEX_MIN, (y * VERTEX_GAP) + VERTEX_MAX, (z * VERTEX_GAP) + VERTEX_MAX), glm::vec2(0.0f, 1.0f), 0.0f)
                    ));
                }
                if (block & LEFT_SIDE) {
                    quads.emplace_back(Quad(
                            Vertex(glm::vec3((x * VERTEX_GAP) + VERTEX_MIN, (y * VERTEX_GAP) + VERTEX_MAX, (z * VERTEX_GAP) + VERTEX_MAX), glm::vec2(1.0f, 0.0f), 0.0f),
                            Vertex(glm::vec3((x * VERTEX_GAP) + VERTEX_MIN, (y * VERTEX_GAP) + VERTEX_MAX, (z * VERTEX_GAP) + VERTEX_MIN), glm::vec2(1.0f, 1.0f), 0.0f),
                            Vertex(glm::vec3((x * VERTEX_GAP) + VERTEX_MIN, (y * VERTEX_GAP) + VERTEX_MIN, (z * VERTEX_GAP) + VERTEX_MIN), glm::vec2(0.0f, 1.0f), 0.0f),
                            Vertex(glm::vec3((x * VERTEX_GAP) + VERTEX_MIN, (y * VERTEX_GAP) + VERTEX_MIN, (z * VERTEX_GAP) + VERTEX_MAX), glm::vec2(0.0f, 0.0f), 0.0f)
                    ));
                }
                if (block & RIGHT_SIDE) {
                    quads.emplace_back(Quad(
                            Vertex(glm::vec3((x * VERTEX_GAP) + VERTEX_MAX, (y * VERTEX_GAP) + VERTEX_MAX, (z * VERTEX_GAP) + VERTEX_MAX), glm::vec2(1.0f, 0.0f), 0.0f),
                            Vertex(glm::vec3((x * VERTEX_GAP) + VERTEX_MAX, (y * VERTEX_GAP) + VERTEX_MAX, (z * VERTEX_GAP) + VERTEX_MIN), glm::vec2(1.0f, 1.0f), 0.0f),
                            Vertex(glm::vec3((x * VERTEX_GAP) + VERTEX_MAX, (y * VERTEX_GAP) + VERTEX_MIN, (z * VERTEX_GAP) + VERTEX_MIN), glm::vec2(0.0f, 1.0f), 0.0f),
                            Vertex(glm::vec3((x * VERTEX_GAP) + VERTEX_MAX, (y * VERTEX_GAP) + VERTEX_MIN, (z * VERTEX_GAP) + VERTEX_MAX), glm::vec2(0.0f, 0.0f), 0.0f)
                    ));
                }
                if (block & BOTTOM_SIDE) {
                    quads.emplace_back(Quad(
                            Vertex(glm::vec3((x * VERTEX_GAP) + VERTEX_MIN, (y * VERTEX_GAP) + VERTEX_MIN, (z * VERTEX_GAP) + VERTEX_MIN), glm::vec2(0.0f, 1.0f), 0.0f),
                            Vertex(glm::vec3((x * VERTEX_GAP) + VERTEX_MAX, (y * VERTEX_GAP) + VERTEX_MIN, (z * VERTEX_GAP) + VERTEX_MIN), glm::vec2(1.0f, 1.0f), 0.0f),
                            Vertex(glm::vec3((x * VERTEX_GAP) + VERTEX_MAX, (y * VERTEX_GAP) + VERTEX_MIN, (z * VERTEX_GAP) + VERTEX_MAX), glm::vec2(1.0f, 0.0f), 0.0f),
                            Vertex(glm::vec3((x * VERTEX_GAP) + VERTEX_MIN, (y * VERTEX_GAP) + VERTEX_MIN, (z * VERTEX_GAP) + VERTEX_MAX), glm::vec2(0.0f, 0.0f), 0.0f)
                    ));
                }
                if (block & TOP_SIDE) {
                    quads.emplace_back(Quad(
                            Vertex(glm::vec3((x * VERTEX_GAP) + VERTEX_MIN, (y * VERTEX_GAP) + VERTEX_MAX, (z * VERTEX_GAP) + VERTEX_MIN), glm::vec2(0.0f, 1.0f), 0.0f),
                            Vertex(glm::vec3((x * VERTEX_GAP) + VERTEX_MAX, (y * VERTEX_GAP) + VERTEX_MAX, (z * VERTEX_GAP) + VERTEX_MIN), glm::vec2(1.0f, 1.0f), 0.0f),
                            Vertex(glm::vec3((x * VERTEX_GAP) + VERTEX_MAX, (y * VERTEX_GAP) + VERTEX_MAX, (z * VERTEX_GAP) + VERTEX_MAX), glm::vec2(1.0f, 0.0f), 0.0f),
                            Vertex(glm::vec3((x * VERTEX_GAP) + VERTEX_MIN, (y * VERTEX_GAP) + VERTEX_MAX, (z * VERTEX_GAP) + VERTEX_MAX), glm::vec2(0.0f, 0.0f), 0.0f)
                    ));
                }
            }
        }
    }
}
