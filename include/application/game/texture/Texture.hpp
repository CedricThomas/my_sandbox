//
// Created by arzad on 13/04/2022.
//

#ifndef APP_TEXTURE_HPP
#define APP_TEXTURE_HPP


class Texture {
public:
    Texture(unsigned char *data, int width, int height, int channels);
    
    int getWidth() const;

    int getHeight() const;

    int getChannels() const;

    unsigned char *getData() const;

private:
    int _width;
    int _height;
    int _channels;
    unsigned char *_data;
};


#endif //APP_TEXTURE_HPP
