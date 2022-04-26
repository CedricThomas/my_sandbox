//
// Created by arzad on 23/03/2022.
//

#include "application/game/renderer/voxel/Mesher.hpp"

Mesher::Mesher(
        std::shared_ptr<BundleAtlas> bundleAtlas,
        std::shared_ptr<TextureAtlas> textureAtlas,
        QuadsMap &quadsMap
) : _bundleAtlas(std::move(bundleAtlas)),
    _textureAtlas(std::move(textureAtlas)),
    _quadsMap(quadsMap),
    _chunkMap(),
    _meshMap(),
    _meshUpdates() {}

QuadBuffer Mesher::generateQuadBuffer(const Chunk &chunk, const Mesh &mesh) {
    QuadBuffer quads;
    for (int y = 0; y < CHUNK_HEIGHT; y++) {
        for (int x = 0; x < CHUNK_WIDTH; x++) {
            for (int z = 0; z < CHUNK_WIDTH; z++) {
                unsigned char block = mesh.get(x, y, z);
                if (block == 0)
                    continue;
                auto blockID = chunk.data.get(x, y, z);
                auto map = _bundleAtlas->getBlockTemplate(blockID).textureMapping;
                if (block & BACK_SIDE) {
                    auto region = _textureAtlas->getBlockTextureRegion(blockID.first, map.back);
                    quads.emplace_back(Quad(
                            Vertex(
                                    glm::vec3(
                                            (x * VERTEX_GAP) + VERTEX_MIN,
                                            (y * VERTEX_GAP) + VERTEX_MIN,
                                            (z * VERTEX_GAP) + VERTEX_MIN
                                    ),
                                    glm::vec2(region.x, region.y + region.w),
                                    0.0f
                            ),
                            Vertex(
                                    glm::vec3(
                                            (x * VERTEX_GAP) + VERTEX_MAX,
                                            (y * VERTEX_GAP) + VERTEX_MIN,
                                            (z * VERTEX_GAP) + VERTEX_MIN
                                    ),
                                    glm::vec2(region.x + region.z, region.y + region.w),
                                    0.0f
                            ),
                            Vertex(
                                    glm::vec3(
                                            (x * VERTEX_GAP) + VERTEX_MAX,
                                            (y * VERTEX_GAP) + VERTEX_MAX,
                                            (z * VERTEX_GAP) + VERTEX_MIN
                                    ),
                                    glm::vec2(region.x + region.z, region.y),
                                    0.0f
                            ),
                            Vertex(
                                    glm::vec3(
                                            (x * VERTEX_GAP) + VERTEX_MIN,
                                            (y * VERTEX_GAP) + VERTEX_MAX,
                                            (z * VERTEX_GAP) + VERTEX_MIN
                                    ),
                                    glm::vec2(region.x, region.y),
                                    0.0f
                            )
                    ));
                }
                if (block & FRONT_SIDE) {
                    auto region = _textureAtlas->getBlockTextureRegion(blockID.first, map.front);
                    quads.emplace_back(Quad(
                            Vertex(
                                    glm::vec3(
                                            (x * VERTEX_GAP) + VERTEX_MIN,
                                            (y * VERTEX_GAP) + VERTEX_MIN,
                                            (z * VERTEX_GAP) + VERTEX_MAX
                                    ),
                                    glm::vec2(region.x, region.y + region.w),
                                    0.0f
                            ),
                            Vertex(
                                    glm::vec3(
                                            (x * VERTEX_GAP) + VERTEX_MAX,
                                            (y * VERTEX_GAP) + VERTEX_MIN,
                                            (z * VERTEX_GAP) + VERTEX_MAX
                                    ),
                                    glm::vec2(region.x + region.z, region.y + region.w),
                                    0.0f
                            ),
                            Vertex(
                                    glm::vec3(
                                            (x * VERTEX_GAP) + VERTEX_MAX,
                                            (y * VERTEX_GAP) + VERTEX_MAX,
                                            (z * VERTEX_GAP) + VERTEX_MAX
                                    ),
                                    glm::vec2(region.x + region.z, region.y),
                                    0.0f
                            ),
                            Vertex(
                                    glm::vec3(
                                            (x * VERTEX_GAP) + VERTEX_MIN,
                                            (y * VERTEX_GAP) + VERTEX_MAX,
                                            (z * VERTEX_GAP) + VERTEX_MAX
                                    ),
                                    glm::vec2(region.x, region.y),
                                    0.0f
                            )
                    ));
                }
                if (block & LEFT_SIDE) {
                    auto region = _textureAtlas->getBlockTextureRegion(blockID.first, map.left);
                    quads.emplace_back(Quad(
                            Vertex(
                                    glm::vec3(
                                            (x * VERTEX_GAP) + VERTEX_MIN,
                                            (y * VERTEX_GAP) + VERTEX_MAX,
                                            (z * VERTEX_GAP) + VERTEX_MAX
                                    ),
                                    glm::vec2(region.x + region.z, region.y),
                                    0.0f
                            ),
                            Vertex(
                                    glm::vec3(
                                            (x * VERTEX_GAP) + VERTEX_MIN,
                                            (y * VERTEX_GAP) + VERTEX_MAX,
                                            (z * VERTEX_GAP) + VERTEX_MIN
                                    ),
                                    glm::vec2(region.x, region.y),
                                    0.0f
                            ),
                            Vertex(
                                    glm::vec3(
                                            (x * VERTEX_GAP) + VERTEX_MIN,
                                            (y * VERTEX_GAP) + VERTEX_MIN,
                                            (z * VERTEX_GAP) + VERTEX_MIN
                                    ),
                                    glm::vec2(region.x, region.y + region.z),
                                    0.0f
                            ),
                            Vertex(
                                    glm::vec3(
                                            (x * VERTEX_GAP) + VERTEX_MIN,
                                            (y * VERTEX_GAP) + VERTEX_MIN,
                                            (z * VERTEX_GAP) + VERTEX_MAX
                                    ),
                                    glm::vec2(region.x + region.z, region.y + region.z),
                                    0.0f
                            )
                    ));
                }
                if (block & RIGHT_SIDE) {
                    auto region = _textureAtlas->getBlockTextureRegion(blockID.first, map.right);
                    quads.emplace_back(Quad(
                            Vertex(
                                    glm::vec3(
                                            (x * VERTEX_GAP) + VERTEX_MAX,
                                            (y * VERTEX_GAP) + VERTEX_MAX,
                                            (z * VERTEX_GAP) + VERTEX_MAX),
                                    glm::vec2(region.x + region.z, region.y),
                                    0.0f
                            ),
                            Vertex(
                                    glm::vec3(
                                            (x * VERTEX_GAP) + VERTEX_MAX,
                                            (y * VERTEX_GAP) + VERTEX_MAX,
                                            (z * VERTEX_GAP) + VERTEX_MIN
                                    ),
                                    glm::vec2(region.x, region.y),
                                    0.0f
                            ),
                            Vertex(
                                    glm::vec3(
                                            (x * VERTEX_GAP) + VERTEX_MAX,
                                            (y * VERTEX_GAP) + VERTEX_MIN,
                                            (z * VERTEX_GAP) + VERTEX_MIN),
                                    glm::vec2(region.x, region.y + region.w),
                                    0.0f
                            ),
                            Vertex(
                                    glm::vec3(
                                            (x * VERTEX_GAP) + VERTEX_MAX,
                                            (y * VERTEX_GAP) + VERTEX_MIN,
                                            (z * VERTEX_GAP) + VERTEX_MAX),
                                    glm::vec2(region.x + region.z, region.y + region.w),
                                    0.0f
                            )
                    ));
                }
                if (block & BOTTOM_SIDE) {
                    auto region = _textureAtlas->getBlockTextureRegion(blockID.first, map.bottom);
                    quads.emplace_back(Quad(
                            Vertex(
                                    glm::vec3(
                                            (x * VERTEX_GAP) + VERTEX_MIN,
                                            (y * VERTEX_GAP) + VERTEX_MIN,
                                            (z * VERTEX_GAP) + VERTEX_MIN
                                    ),
                                    glm::vec2(region.x, region.y),
                                    0.0f
                            ),
                            Vertex(
                                    glm::vec3(
                                            (x * VERTEX_GAP) + VERTEX_MAX,
                                            (y * VERTEX_GAP) + VERTEX_MIN,
                                            (z * VERTEX_GAP) + VERTEX_MIN
                                    ),
                                    glm::vec2(region.x + region.z, region.y),
                                    0.0f
                            ),
                            Vertex(
                                    glm::vec3(
                                            (x * VERTEX_GAP) + VERTEX_MAX,
                                            (y * VERTEX_GAP) + VERTEX_MIN,
                                            (z * VERTEX_GAP) + VERTEX_MAX
                                    ),
                                    glm::vec2(region.x + region.z, region.y + region.w),
                                    0.0f
                            ),
                            Vertex(
                                    glm::vec3(
                                            (x * VERTEX_GAP) + VERTEX_MIN,
                                            (y * VERTEX_GAP) + VERTEX_MIN,
                                            (z * VERTEX_GAP) + VERTEX_MAX
                                    ),
                                    glm::vec2(region.x, region.y + region.w),
                                    0.0f
                            )
                    ));
                }
                if (block & TOP_SIDE) {
                    auto region = _textureAtlas->getBlockTextureRegion(blockID.first, map.top);
                    quads.emplace_back(Quad(
                            Vertex(
                                    glm::vec3(
                                            (x * VERTEX_GAP) + VERTEX_MIN,
                                            (y * VERTEX_GAP) + VERTEX_MAX,
                                            (z * VERTEX_GAP) + VERTEX_MIN
                                    ),
                                    glm::vec2(region.x, region.y),
                                    0.0f
                            ),
                            Vertex(
                                    glm::vec3(
                                            (x * VERTEX_GAP) + VERTEX_MAX,
                                            (y * VERTEX_GAP) + VERTEX_MAX,
                                            (z * VERTEX_GAP) + VERTEX_MIN),
                                    glm::vec2(region.x + region.z, region.y),
                                    0.0f
                            ),
                            Vertex(
                                    glm::vec3(
                                            (x * VERTEX_GAP) + VERTEX_MAX,
                                            (y * VERTEX_GAP) + VERTEX_MAX,
                                            (z * VERTEX_GAP) + VERTEX_MAX),
                                    glm::vec2(region.x + region.z, region.y + region.w),
                                    0.0f
                            ),
                            Vertex(
                                    glm::vec3(
                                            (x * VERTEX_GAP) + VERTEX_MIN,
                                            (y * VERTEX_GAP) + VERTEX_MAX,
                                            (z * VERTEX_GAP) + VERTEX_MAX),
                                    glm::vec2(region.x, region.y + region.w),
                                    0.0f
                            )
                    ));
                }
            }
        }
    }
    return quads;
}

Mesh Mesher::meshChunk(const Chunk &chunk) {
    auto &blocks = chunk.data;
    Mesh mesh(blocks.getX(), blocks.getY(), blocks.getZ());
    for (int y = 0; y < CHUNK_HEIGHT; y++) {
        for (int x = 0; x < CHUNK_WIDTH; x++) {
            for (int z = 0; z < CHUNK_WIDTH; z++) {

                // if the current block is empty skip it
                if (blocks.get(x, y, z).second == 0)
                    continue;
                unsigned char block = 0;
                // if the adjacent block is not empty, doesnt add the face to the mesh
                // if the adjacent block is empty, add the face to the mesh
                // if the adjacent block is outside the blocks, add the face to the mesh
                if (y == 0 || blocks.get(x, y - 1, z).second == 0)
                    block |= BOTTOM_SIDE;
                if (y == CHUNK_HEIGHT - 1 || blocks.get(x, y + 1, z).second == 0)
                    block |= TOP_SIDE;
                if (x == 0 || blocks.get(x - 1, y, z).second == 0)
                    block |= LEFT_SIDE;
                if (x == CHUNK_WIDTH - 1 || blocks.get(x + 1, y, z).second == 0)
                    block |= RIGHT_SIDE;
                if (z == CHUNK_WIDTH - 1 || blocks.get(x, y, z + 1).second == 0)
                    block |= FRONT_SIDE;
                if (z == 0 || blocks.get(x, y, z - 1).second == 0)
                    block |= BACK_SIDE;
                mesh.set(x, y, z, block);
            }
        }
    }
    return mesh;
}

void Mesher::insertChunk(const Chunk &chunk) {
    _chunkMap.emplace(chunk.position, chunk);
    auto mesh = meshChunk(chunk);
    _meshMap.emplace(chunk.position, mesh);

    _meshUpdates.insert(chunk.position);
    // try to update adjacent meshes if cannot doesn't add to the update list
    if (removeMeshCommonFaces(chunk.position, RIGHT_SIDE))
        _meshUpdates.insert(chunk.position + glm::vec3(1, 0, 0));
    if (removeMeshCommonFaces(chunk.position, LEFT_SIDE))
        _meshUpdates.insert(chunk.position + glm::vec3(-1, 0, 0));
    if (removeMeshCommonFaces(chunk.position, BACK_SIDE))
        _meshUpdates.insert(chunk.position + glm::vec3(0, 0, -1));
    if (removeMeshCommonFaces(chunk.position, FRONT_SIDE))
        _meshUpdates.insert(chunk.position + glm::vec3(0, 0, 1));
}

void Mesher::removeChunk(const glm::vec3 &position) {
    _chunkMap.erase(position);
    _meshMap.erase(position);

    // tell the renderer to remove the quad buffer for this chunk
    _meshUpdates.insert(position);

    // force to mesh the faces of the adjacent chunks
    // RIGHT
    if (generateChunkSideMesh(position + glm::vec3(-1, 0, 0), RIGHT_SIDE))
        _meshUpdates.insert(position + glm::vec3(-1, 0, 0));
    // LEFT
    if (generateChunkSideMesh(position + glm::vec3(1, 0, 0), LEFT_SIDE))
        _meshUpdates.insert(position + glm::vec3(1, 0, 0));
    // BACK
    if (generateChunkSideMesh(position + glm::vec3(0, 0, 1), BACK_SIDE))
        _meshUpdates.insert(position + glm::vec3(0, 0, 1));
    // FRONT
    if (generateChunkSideMesh(position + glm::vec3(0, 0, -1), FRONT_SIDE))
        _meshUpdates.insert(position + glm::vec3(0, 0, -1));
}

void Mesher::generateVertexes() {
    for (auto update: _meshUpdates) {
        auto meshIt = _meshMap.find(update);
        // if the mesh is not found, remove it from the quads map and continue
        if (meshIt == _meshMap.end()) {
            _quadsMap.erase(update);
            continue;
        }
        auto &mesh = meshIt->second;
        auto buffer = generateQuadBuffer(_chunkMap.at(update), mesh);
        _quadsMap.emplace(update, buffer).first->second = buffer;
    }
    _meshUpdates.clear();

}

bool Mesher::generateChunkSideMesh(const glm::vec3 &position, int side) {
    if (_chunkMap.find(position) == _chunkMap.end() || _meshMap.find(position) == _meshMap.end())
        return false;
    auto update = false;
    auto &chunk = _chunkMap.at(position);
    auto &mesh = _meshMap.at(position);

    // offset of the chunk axes
    auto xOffset = (side & LEFT_SIDE) ? 0 : (CHUNK_WIDTH - 1);
    auto zOffset = (side & BACK_SIDE) ? 0 : (CHUNK_WIDTH - 1);

    // regenerate the mesh side based on the chunk block
    for (auto y = 0; y < CHUNK_HEIGHT; y++) {
        for (auto xz = 0; xz < CHUNK_WIDTH; xz++) {
            // choose the side axe
            if (side & (LEFT_SIDE | RIGHT_SIDE)) {
                if (chunk.data.get(xOffset, y, xz).second != 0) {
                    mesh.set(xOffset, y, xz, mesh.get(xOffset, y, xz) | side);
                    update = true;
                }
            } else {
                if (chunk.data.get(xz, y, zOffset).second != 0) {
                    mesh.set(xz, y, zOffset, mesh.get(xz, y, zOffset) | side);
                    update = true;
                }
            }
        }
    }
    return update;
}

bool Mesher::removeMeshCommonFaces(const glm::vec3 &position, int side) {
    auto sideToVectorMapping = std::unordered_map<int, glm::vec3>{
            {LEFT_SIDE,  glm::vec3(-1, 0, 0)},
            {RIGHT_SIDE, glm::vec3(1, 0, 0)},
            {FRONT_SIDE, glm::vec3(0, 0, 1)},
            {BACK_SIDE,  glm::vec3(0, 0, -1)}
    };
    auto aPosition = position;
    auto bPosition = position + sideToVectorMapping.at(side);

    if (_meshMap.find(aPosition) == _meshMap.end() ||
        _meshMap.find(bPosition) == _meshMap.end())
        return false;

    auto revereSideMapping = std::unordered_map<int, int>{
            {LEFT_SIDE,  RIGHT_SIDE},
            {RIGHT_SIDE, LEFT_SIDE},
            {FRONT_SIDE, BACK_SIDE},
            {BACK_SIDE,  FRONT_SIDE}
    };

    auto &a = _meshMap.at(aPosition);
    auto &b = _meshMap.at(bPosition);
    auto &aSide = side;
    auto &bSide = revereSideMapping.at(side);

    // offset of the chunk axes for each chunk
    auto axOffset = (aSide & LEFT_SIDE) ? 0 : (CHUNK_WIDTH - 1);
    auto bxOffset = (bSide & LEFT_SIDE) ? 0 : (CHUNK_WIDTH - 1);

    auto azOffset = (aSide & BACK_SIDE) ? 0 : (CHUNK_WIDTH - 1);
    auto bzOffset = (bSide & BACK_SIDE) ? 0 : (CHUNK_WIDTH - 1);

    auto update = false;
    for (auto y = 0; y < CHUNK_HEIGHT; y++) {
        for (auto xz = 0; xz < CHUNK_WIDTH; xz++) {
            // choose the side axe
            if (aSide & (LEFT_SIDE | RIGHT_SIDE)) {
                auto aBlock = a.get(axOffset, y, xz);
                auto bBlock = b.get(bxOffset, y, xz);
                if (aBlock & aSide && bBlock & bSide) {
                    a.set(axOffset, y, xz, aBlock & ~aSide);
                    b.set(bxOffset, y, xz, bBlock & ~bSide);
                    update = true;
                }
            } else {
                auto aBlock = a.get(xz, y, azOffset);
                auto bBlock = b.get(xz, y, bzOffset);
                if (aBlock & aSide && bBlock & bSide) {
                    a.set(xz, y, azOffset, aBlock & ~aSide);
                    b.set(xz, y, bzOffset, bBlock & ~bSide);
                    update = true;
                }
            }
        }
    }
    return update;
}
