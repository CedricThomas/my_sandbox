//
// Created by arzad on 12/04/2022.
//

#ifndef APP_BUNDLEATLAS_HPP
#define APP_BUNDLEATLAS_HPP

#include <unordered_map>
#include "Bundle.hpp"

class BundleAtlas {
public:
    void registerBundle(const Bundle &bundle);
    const BlockTemplate &getBlockTemplate(BlockTemplateBundledID id) const;

    BundleAtlas() = default;
private:
    std::unordered_map<BundleID, Bundle> _atlas;
};


#endif //APP_BUNDLEATLAS_HPP
