//
// Created by arzad on 11/04/2022.
//

#ifndef APP_BUNDLE_HPP
#define APP_BUNDLE_HPP


#include <string>
#include "world/blocks/BlockTemplate.hpp"

using BundleID = unsigned short;
using BlockTemplateBundledID = std::pair<BundleID , BlockTemplateID>;

struct Bundle {
    Bundle(BundleID id, std::string root, const std::string &name, const std::vector<BlockTemplate> &blocks);

    BundleID ID;
    std::string root;
    std::string name;
    std::unordered_map<BlockTemplateID, BlockTemplate> blocks;
};

#endif //APP_BUNDLE_HPP
