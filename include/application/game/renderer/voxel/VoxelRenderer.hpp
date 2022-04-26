//
// Created by arzad on 17/01/2022.
//

#ifndef APP_VOXELRENDERER_HPP
#define APP_VOXELRENDERER_HPP

#include "application/game/renderer/ARenderer.hpp"
#include "application/game/renderer/Shader.hpp"
#include "application/game/Camera.hpp"
#include "application/game/renderer/RenderingTracker.hpp"
#include "world/World.hpp"
#include "application/game/renderer/voxel/containers/QuadBuffer.hpp"
#include "application/game/renderer/voxel/Mesher.hpp"
#include "bundling/BundleAtlas.hpp"
#include "application/game/texture/TextureAtlas.hpp"

#define MAX_VERTEXES_PER_DRAW (MAX_QUADS_PER_DRAW * 4)
#define MAX_INDEXES_PER_DRAW (MAX_QUADS_PER_DRAW * 6)


class VoxelRenderer : public ARenderer {
public:
    explicit VoxelRenderer(
            std::shared_ptr<QuadsMap> _quadsMap,
            std::shared_ptr<TextureAtlas> textureAtlas
    );

    virtual ~VoxelRenderer();

    void render(AGame &game) override;

private:
    GLuint _vao;
    GLuint _vbo;
    GLuint _ebo;
    GLuint _textureAtlas;
    Shader _shader;
    std::shared_ptr<QuadsMap> _quadsMap;
    std::shared_ptr<TextureAtlas> _atlas;
};


#endif //APP_VOXELRENDERER_HPP
