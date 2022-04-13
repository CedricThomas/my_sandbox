//
// Created by arzad on 13/04/2022.
//

#include "application/texture/Texture.hpp"

Texture::Texture(unsigned char *data, int width, int height, int channels) : _data(nullptr), _width(width), _height(height),
                                                                    _channels(channels) {
    _data = new unsigned char[_width * _height * 4];
    for (int i = 0; i < width * height * 4; i += 4) {
        _data[i] = data[i];
        _data[i + 1] = data[i + 1];
        _data[i + 2] = data[i + 2];
        // This part right here checks to see how many channels the image has, and if there's only 3, we add our own 4th channel.
        if (channels == 3)
            _data[i + 3] = 255;
        else
            _data[i + 3] = data[i + 3];
    }

}

int Texture::getWidth() const {
    return _width;
}

int Texture::getHeight() const {
    return _height;
}

int Texture::getChannels() const {
    return _channels;
}

unsigned char *Texture::getData() const {
    return _data;
}
