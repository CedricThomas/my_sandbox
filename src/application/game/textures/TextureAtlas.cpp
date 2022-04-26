//
// Created by arzad on 06/04/2022.
//

#include <stdexcept>
#include "application/game/texture/TextureAtlas.hpp"
#include "lib/resources/ResourcesFinder.hpp"
#include "lib/stb_image.h"
#include "lib/stb_image_write.h"
#include "spdlog/spdlog.h"

void TextureAtlas::loadBundleBlockTextures(const Bundle &bundle) {
    bool first = true;
    int width;
    int height;
    int nrChannels;
    const auto blockTextures = ResourcesFinder(bundle.root)
            .append(TEXTURES_FOLDER)
            .append(BLOCKS_FOLDER)
            .list();
    for (const auto &blockTexture: blockTextures) {
        auto data = stbi_load(blockTexture.path.c_str(), &width, &height, &nrChannels, 4);
        if (!data)
            throw std::runtime_error("Cant load texture: " + blockTexture.path);
        if (width != height) {
            stbi_image_free(data);
            throw std::runtime_error("Texture: " + blockTexture.path + " is not square");
        }
        if (first) {
            _width = width;
            first = false;
        } else if (_width != width) {
            throw std::runtime_error("Texture: " + blockTexture.path + " has different width");
        }
        spdlog::info("Loading texture {} from bundle {}", blockTexture.path, bundle.ID);
        _texturesLocations.insert({
                                          std::make_pair(bundle.ID, blockTexture.basename),
                                          {
                                                  Texture(data, width, height, nrChannels),
                                                  glm::vec4(),
                                          }
                                  });
    }
}

void TextureAtlas::generateAtlas() {
    int atlasSize = 0;
    while (atlasSize * atlasSize < _texturesLocations.size())
        atlasSize++;
    delete[] _data;
    _data = new unsigned char[atlasSize * atlasSize * _width * _width * 4];
    std::memset(_data, 0, atlasSize * atlasSize *_width * _width * 4);
    auto textureIndex = 0;
    auto atlasTextureX = 0;
    auto atlasTextureY = 0;
    auto atlasTextureWidth = _width * atlasSize;
    for (auto &textureLocation: _texturesLocations) {
        auto &textureRegion = textureLocation.second;
        auto texture = textureRegion.texture.getData();
        for (int texturePixelY = 0; texturePixelY < _width; texturePixelY++) {
            for (int texturePixelX = 0; texturePixelX < _width; texturePixelX++) {
                auto atlasPixelX = atlasTextureX * _width * 4 + texturePixelX * 4;
                auto atlasPixelY = atlasTextureY * _width * 4 + texturePixelY * 4;
                _data[(atlasPixelY * atlasTextureWidth) + atlasPixelX + 0] = texture[(texturePixelY * _width * 4) + (texturePixelX * 4) + 0];
                _data[(atlasPixelY * atlasTextureWidth) + atlasPixelX + 1] = texture[(texturePixelY * _width * 4) + (texturePixelX * 4) + 1];
                _data[(atlasPixelY * atlasTextureWidth) + atlasPixelX + 2] = texture[(texturePixelY * _width * 4) + (texturePixelX * 4) + 2];
                _data[(atlasPixelY * atlasTextureWidth) + atlasPixelX + 3] = texture[(texturePixelY * _width * 4) + (texturePixelX * 4) + 3];
            }
        }
        textureRegion.region = glm::vec4(
                (float)(atlasTextureX * _width) / (float)(atlasSize * _width),
                (float)(atlasTextureY * _width) / (float)(atlasSize * _width),
                (float)(_width) / (float)(atlasSize * _width),
                (float)(_width) / (float)(atlasSize * _width)
        );
        textureIndex += 1;
        atlasTextureX = textureIndex % atlasSize;
        atlasTextureY = textureIndex / atlasSize;
    }
    _atlasWidth = atlasSize * _width;
    _atlasHeight = atlasSize * _width;
    stbi_write_png("output.png", atlasSize*_width, atlasSize*_width, 4, _data, atlasSize*_width*4);
}

const glm::vec4 TextureAtlas::getBlockTextureRegion(const BundleID &id, const std::string &textureName) const {
    return _texturesLocations.at(std::make_pair(id, textureName)).region;
}

unsigned char *TextureAtlas::getAtlas() const {
    return _data;
}

unsigned int TextureAtlas::getAtlasWidth() const {
    return _atlasWidth;
}

unsigned int TextureAtlas::getAtlasHeight() const {
    return _atlasHeight;
}
