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
                BlockTemplate(0, "", NONE, true, false),
                BlockTemplate(1, "dirt"),
                BlockTemplate(2, "grass", BOTTOM_TOP_SIDE),
                BlockTemplate(3, "stone"),
                BlockTemplate(4, "stone_brick"),
        }
};

#endif //APP_DEFAULTBLOCKBUNDLE_HPP
