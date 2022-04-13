//
// Created by arzad on 23/03/2022.
//

#ifndef APP_MESHER_HPP
#define APP_MESHER_HPP

#include <unordered_set>
#include "glm/gtx/hash.hpp"
#include "application/renderer/containers/QuadBuffer.hpp"
#include "world/World.hpp"
#include "lib/containers/Flat3DArray.hpp"
#include "bundling/BundleAtlas.hpp"
#include "application/texture/TextureAtlas.hpp"

using Mesh = Flat3DArray<unsigned char>;
using MeshMap = std::unordered_map<glm::vec3, Mesh, std::hash<glm::vec3>>;

#define TOP_SIDE (1 << 0) // 1
#define BOTTOM_SIDE (1 << 1)// 2
#define LEFT_SIDE (1 << 2)// 4
#define RIGHT_SIDE (1 << 3) // 8
#define FRONT_SIDE (1 << 4)// 16
#define BACK_SIDE (1 << 5)// 32

#define VERTEX_MIN (-0.1)
#define VERTEX_MAX (0.1)
#define VERTEX_GAP (VERTEX_MAX - VERTEX_MIN)

#define CHUNK_GAP (VERTEX_GAP * CHUNK_WIDTH)

class Mesher {
public:
    explicit Mesher(QuadsMap &quadsMap);
    void insertChunk(const Chunk &chunk);
    void removeChunk(const glm::vec3 &position);
    void generateVertexes(const BundleAtlas &bundleAtlas, const TextureAtlas &textureAtlas);
private:
    // mesh a single chunk and return it
    static Mesh meshChunk(const Chunk &chunk);
    // generate a single quad buffer and return it
    static QuadBuffer generateQuadBuffer(const Chunk &chunk, const Mesh &mesh, const BundleAtlas &bundleAtlas, const TextureAtlas &textureAtlas);

    // generate a chunk side mesh from the mesh map
    // it returns true if an update is needed
    bool generateChunkSideMesh(const glm::vec3 &position, int side);
    // remove common faces from 2 adjacent chunks
    // it returns true if an update is needed
    bool removeMeshCommonFaces(const glm::vec3 &position, int side);

    QuadsMap &_quadsMap;
    ChunkMap _chunkMap;
    MeshMap _meshMap;
    std::unordered_set<glm::vec3, std::hash<glm::vec3>> _meshUpdates;
};


#endif //APP_MESHER_HPP
