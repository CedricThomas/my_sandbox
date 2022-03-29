//
// Created by arzad on 20/02/2022.
//

#ifndef APP_FLAT3DARRAY_HPP
#define APP_FLAT3DARRAY_HPP

#include <vector>
#include <stdexcept>
#include <iostream>
#include "spdlog/spdlog.h"

template<typename T>
class Flat3DArray {
public:
    Flat3DArray(std::vector<T> data, int x, int y, int z) : _x(x), _y(y), _z(z), _data(data) {}

    Flat3DArray(int x, int y, int z) : _x(x), _y(y), _z(z) {
        _data.resize(x * y * z);
    }

    ~Flat3DArray() = default;

    T get(int x, int y, int z) const {
        return _data[x + (_x * _z * y) + (_x * z)];
    }

    void set(int x, int y, int z, T value) {
        _data[x + (_x * _z * y) + (_x * z)] = value;
    }

    int size() {
        return _data.size();
    }

    int getX() const {
        return _x;
    }

    int getY() const {
        return _y;
    }

    int getZ() const {
        return _z;
    }

    const std::vector<T> &getData() const {
        return _data;
    }

    static Flat3DArray<T> unzip(void *data, int x, int y, int z) {
        std::vector<T> newData(x * y * z);
        auto size = 0;
        auto begin = newData.begin();

        while (size < x * y * z) {
            auto block = *((unsigned short *) data);
            auto value = *((T *) (static_cast<char*>(data) + sizeof(short)));
            if (size + block > x * y * z) {
                throw std::runtime_error("Invalid unzip");
            }
            std::fill(begin, begin + block, value);
            begin += block;
            size += block;
            data = static_cast<char*>(data) + sizeof(short) + sizeof(T);
        }

        return Flat3DArray<T>(newData, x, y, z);
    }

private:
    int _x, _y, _z;
    std::vector<T> _data;
};

#endif //APP_FLAT3DARRAY_HPP
