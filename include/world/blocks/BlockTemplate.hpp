//
// Created by arzad on 10/04/2022.
//

#ifndef APP_BLOCKTEMPLATE_HPP
#define APP_BLOCKTEMPLATE_HPP

#include <string>
#include <vector>
#include "lib/containers/PairHash.hpp"

using BlockTemplateID = unsigned short;

struct TextureMapping {
    std::string top;
    std::string bottom;
    std::string left;
    std::string right;
    std::string front;
    std::string back;

    TextureMapping(
            std::string top,
            std::string bottom,
            std::string left,
            std::string right,
            std::string front,
            std::string back
    );

    explicit TextureMapping(const std::string &all);
    TextureMapping(const std::string &top, const std::string &bottom, const std::string &sides);
};

struct BlockTemplate {

    BlockTemplate(
            BlockTemplateID id,
            const TextureMapping &textureMapping,
            bool transparent = false,
            bool solid = true
    );

    BlockTemplateID id;
    TextureMapping textureMapping;
    bool transparent;
    bool solid;
};

#endif //APP_BLOCKTEMPLATE_HPP
