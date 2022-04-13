//
// Created by arzad on 11/04/2022.
//

#include "bundling/Bundle.hpp"

#include <utility>

Bundle::Bundle(BundleID id, std::string root, const std::string &name, const std::vector<BlockTemplate> &blocks)
        : ID(id), root(std::move(root)), name(name), blocks() {
    for (const auto &block: blocks) {
        this->blocks.emplace(std::make_pair(block.id, block));
    }
}
