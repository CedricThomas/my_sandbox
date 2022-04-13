//
// Created by arzad on 06/04/2022.
//

#include "application/texture/TextureAtlas.hpp"

TextureAtlas *TextureAtlas::getInstance() {
    static TextureAtlas instance;
    return &instance;
}
