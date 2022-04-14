//
// Created by arzad on 12/04/2022.
//

#include "bundling/BundleAtlas.hpp"

void BundleAtlas::registerBundle(const Bundle &bundle) {
    _atlas.insert(std::make_pair(bundle.ID, bundle));
}

const BlockTemplate &BundleAtlas::getBlockTemplate(BlockTemplateBundledID id) const {
    return _atlas.at(id.first).blocks.at(id.second);
}
