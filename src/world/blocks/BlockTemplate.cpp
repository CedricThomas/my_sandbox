//
// Created by arzad on 10/04/2022.
//

#include "world/blocks/BlockTemplate.hpp"

#include <utility>

BlockTemplate::BlockTemplate(BlockTemplateID id, const TextureMapping &textureMapping,
                             bool transparent, bool solid)
        : id(id), textureMapping(textureMapping),
          transparent(transparent),
          solid(solid) {}

TextureMapping::TextureMapping(
        std::string top,
        std::string bottom,
        std::string left,
        std::string right,
        std::string front,
        std::string back)
        : top(std::move(top)),
          bottom(std::move(bottom)),
          left(std::move(left)),
          right(std::move(right)),
          front(std::move(front)),
          back(std::move(back)) {}

TextureMapping::TextureMapping(const std::string &all)
        : top(all), bottom(all), left(all), right(all), front(all), back(all) {}

TextureMapping::TextureMapping(const std::string &top, const std::string &bottom, const std::string &sides)
: top(top), bottom(bottom), left(sides), right(sides), front(sides), back(sides) {}
