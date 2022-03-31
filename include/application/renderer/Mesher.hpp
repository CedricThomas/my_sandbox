//
// Created by arzad on 23/03/2022.
//

#ifndef APP_MESHER_HPP
#define APP_MESHER_HPP

#include "glm/gtx/hash.hpp"
#include "QuadBuffer.hpp"
#include "world/World.hpp"
#include "lib/containers/Flat3DArray.hpp"

using Mesh = Flat3DArray<unsigned char>;
using MeshMap = std::unordered_map<glm::vec3, Mesh, std::hash<glm::vec3>>;

#define TOP_SIDE (1 << 1)
#define BOTTOM_SIDE (1 << 2)
#define LEFT_SIDE (1 << 3)
#define RIGHT_SIDE (1 << 4)
#define FRONT_SIDE (1 << 5)
#define BACK_SIDE (1 << 6)

#define VERTEX_MIN (-0.1)
#define VERTEX_MAX (0.1)
#define VERTEX_GAP (VERTEX_MAX - VERTEX_MIN)

#define CHUNK_GAP (VERTEX_GAP * CHUNK_WIDTH)

class Mesher {
public:
    explicit Mesher(QuadsMap &quadsMap);
    void insertChunk(const Chunk &chunk);
    void removeChunk(const glm::vec3 &position);
private:
    void meshChunk(const Chunk &chunk);
    void meshChunkSide(const glm::vec3 &position, int side);

    void generateQuadBuffer(QuadBuffer &quads, const Mesh &mesh);

    QuadsMap &_quadsMap;
    ChunkMap _chunkMap;
    MeshMap _meshMap;

};


#endif //APP_MESHER_HPP
