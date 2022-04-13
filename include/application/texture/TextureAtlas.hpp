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

class TextureAtlas {
public:

    static TextureAtlas *getInstance();
    TextureAtlas(const TextureAtlas &) = delete;
    void operator=(const TextureAtlas &) = delete;
private:
    TextureAtlas() = default;
    struct TextureRegion {
        Resource file;
        glm::vec4 region;
    };
    unsigned char *_data;
    std::unordered_map<BlockTemplateKey, TextureRegion, BlockTemplateKeyHash> _texturesLocations;
};


#endif //APP_TEXTUREATLAS_HPP
