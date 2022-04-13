//
// Created by arzad on 10/04/2022.
//

#ifndef APP_BLOCKTEMPLATE_HPP
#define APP_BLOCKTEMPLATE_HPP

#include <string>
#include <vector>
#include "lib/containers/PairHash.hpp"

using BlockTemplateID = unsigned short;

enum TexturingType {
    NONE,
    UNIFORM,
    BOTTOM_TOP_SIDE,
    ALL,
};
using TexturingType = enum TexturingType;

struct BlockTemplate {
    BlockTemplate(
            BlockTemplateID id,
            std::string textureName,
            TexturingType texturingType = UNIFORM,
            bool transparent = false,
            bool solid = true
    );

    BlockTemplateID id;
    std::string textureName;
    TexturingType texturingType;
    bool transparent;
    bool solid;
};

#endif //APP_BLOCKTEMPLATE_HPP
