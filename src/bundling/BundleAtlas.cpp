//
// Created by arzad on 12/04/2022.
//

#include "bundling/BundleAtlas.hpp"

void BundleAtlas::registerBundle(const Bundle &bundle) {
    _atlas.insert(std::make_pair(bundle.ID, bundle));
}

BlockTemplate &BundleAtlas::operator[](BlockTemplateKey key) {
    return _atlas.at(key.first).blocks.at(key.second);
}

BundleAtlas *BundleAtlas::getInstance() {
    static BundleAtlas instance;
    return &instance;
}
