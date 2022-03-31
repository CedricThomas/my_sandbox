//
// Created by arzad on 23/03/2022.
//

#include "application/renderer/Mesher.hpp"

Mesher::Mesher(QuadsMap &quadsMap): _quadsMap(quadsMap), _chunkMap(), _meshMap() {

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

void Mesher::insertChunk(const Chunk &chunk) {
    _chunkMap.emplace(chunk.position, chunk);
    meshChunk(chunk);
}

void Mesher::removeChunk(const glm::vec3 &position) {

}

void Mesher::meshChunk(const Chunk &chunk) {
    auto &blocks = chunk.data;
    Mesh mesh(blocks.getX(), blocks.getY(), blocks.getZ());
    for (int y = 0; y < CHUNK_HEIGHT; y++) {
        for (int x = 0; x < CHUNK_WIDTH; x++) {
            for (int z = 0; z < CHUNK_WIDTH; z++) {
                // if the current block is empty skip it
                if (blocks.get(x, y, z) == 0)
                    continue;
                unsigned char block = 0;
                // if the adjacent block is not empty, doesnt add the face to the mesh
                // if the adjacent block is empty, add the face to the mesh
                // if the adjacent block is outside the blocks, add the face to the mesh
                if (y == 0 || blocks.get(x, y - 1, z) == 0)
                    block |= BOTTOM_SIDE;
                if (y == CHUNK_HEIGHT - 1 || blocks.get(x, y + 1, z) == 0)
                    block |= TOP_SIDE;
                if (x == 0 || blocks.get(x - 1, y, z) == 0)
                    block |= LEFT_SIDE;
                if (x == CHUNK_WIDTH - 1 || blocks.get(x + 1, y, z) == 0)
                    block |= RIGHT_SIDE;
                if (z == CHUNK_WIDTH - 1 || blocks.get(x, y, z + 1) == 0)
                    block |= FRONT_SIDE;
                if (z == 0 || blocks.get(x, y, z - 1) == 0)
                    block |= BACK_SIDE;
                mesh.set(x, y, z, block);
            }
        }
    }
    // TODO fix this
    QuadBuffer quads;
    _meshMap.emplace(chunk.position, mesh);
    generateQuadBuffer(quads, mesh);
    _quadsMap.emplace(chunk.position, quads);
//    meshChunkSide(chunk.position, FRONT_SIDE);
//    meshChunkSide(chunk.position, BACK_SIDE);
//    meshChunkSide(chunk.position, LEFT_SIDE);
//    meshChunkSide(chunk.position, RIGHT_SIDE);
}

void Mesher::meshChunkSide(const glm::vec3 &position, int side) {

}
