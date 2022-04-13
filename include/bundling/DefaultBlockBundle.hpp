//
// Created by arzad on 11/04/2022.
//

#ifndef APP_DEFAULTBLOCKBUNDLE_HPP
#define APP_DEFAULTBLOCKBUNDLE_HPP

#include <vector>
#include "world/blocks/BlockTemplate.hpp"
#include "Bundle.hpp"

#define DEFAULT_BUNDLE_ID 0
#define DEFAULT_BUNDLE_ROOT ""
#define DEFAULT_BUNDLE_NAME "default"

const Bundle DEFAULT_BUNDLE = {
        DEFAULT_BUNDLE_ID,
        DEFAULT_BUNDLE_ROOT,
        DEFAULT_BUNDLE_NAME,
        {
                BlockTemplate(0, TextureMapping{""}, true, false),
                BlockTemplate(1, TextureMapping{"dirt"}),
                BlockTemplate(2, TextureMapping{"grass_block_top", "dirt", "grass_block_side"}),
                BlockTemplate(3, TextureMapping{"stone"}),
                BlockTemplate(4, TextureMapping{"stone_brick"}),
        }
};

#endif //APP_DEFAULTBLOCKBUNDLE_HPP
