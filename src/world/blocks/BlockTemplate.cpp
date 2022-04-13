//
// Created by arzad on 10/04/2022.
//

#include "world/blocks/BlockTemplate.hpp"

#include <utility>

BlockTemplate::BlockTemplate(BlockTemplateID id, std::string textureName,
                             enum TexturingType texturingType,
                             bool transparent, bool solid)
        : id(id),
          transparent(transparent),
          solid(solid), textureName(std::move(textureName)),
          texturingType(texturingType) {}
