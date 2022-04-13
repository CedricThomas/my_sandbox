//
// Created by arzad on 06/04/2022.
//

#ifndef APP_TEXTUREATLAS_HPP
#define APP_TEXTUREATLAS_HPP

#include <unordered_map>
#include <vector>
#include "lib/resources/Resource.hpp"
#include "glm/vec4.hpp"
#include "world/blocks/BlockTemplate.hpp"
#include "bundling/Bundle.hpp"
#include "Texture.hpp"

using TextureBundledID = std::pair<BundleID, std::string>;
using TextureBundledIDHash = PairHash<BundleID, std::string>;

// TODO disable global atlas and load in application constructor
class TextureAtlas {
public:
    static TextureAtlas &getInstance();

    TextureAtlas(const TextureAtlas &) = delete;

    void operator=(const TextureAtlas &) = delete;

private:
    TextureAtlas() = default;

public:
    void loadBundleBlockTextures(const Bundle &bundle);

    void generateAtlas();

    unsigned char *getAtlas() const;

    const glm::vec4 getBlockTextureRegion(const BundleID &id, const std::string &textureName) const;

    struct TextureRegion {
        Texture texture;
        glm::vec4 region;
    };
    unsigned char *_data;
    unsigned int _width;
    std::unordered_map<TextureBundledID, TextureRegion, TextureBundledIDHash> _texturesLocations;
};


#endif //APP_TEXTUREATLAS_HPP
