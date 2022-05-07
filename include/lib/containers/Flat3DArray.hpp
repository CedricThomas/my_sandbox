//
// Created by arzad on 20/02/2022.
//

#ifndef APP_FLAT3DARRAY_HPP
#define APP_FLAT3DARRAY_HPP

#include <vector>
#include <stdexcept>
#include <iostream>
#include <utility>
#include "spdlog/spdlog.h"

template<typename T>
class Flat3DArray {
public:
    Flat3DArray() = default;

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

    static Flat3DArray<T> unzip(size_t total_size, void *data) {
        auto data_ptr = data;
        auto coords = static_cast<int *>(data);
        data = ((unsigned char *) data) + sizeof(int) * 3;
        std::vector<T> newData(coords[0] * coords[1] * coords[2]);
        auto size = 0;
        auto begin = newData.begin();

        while (size < coords[0] * coords[1] * coords[2]) {
            auto block = *((CompressionCounterType *) data);
            auto value = *((T *) (static_cast<unsigned char *>(data) + sizeof(CompressionCounterType)));
            if (size + block > coords[0] * coords[1] * coords[2]) {
                throw std::runtime_error("Invalid unzip");
            }
            std::fill(begin, begin + block, value);
            begin += block;
            size += block;
            data = static_cast<unsigned char *>(data) + sizeof(CompressionCounterType) + sizeof(T);
        }

        if (total_size != ((char *)data - (char *)data_ptr)) {
            throw std::runtime_error(
                    "Invalid unzip : " +
                    std::to_string(total_size) + " != " +
                    std::to_string(((char *)data - (char *)data_ptr))
            );
        }
        spdlog::info("Unzipped {} => {} x {} x {}", newData.size(), coords[0], coords[1], coords[2]);
        return Flat3DArray<T>(newData, coords[0], coords[1], coords[2]);
    }

    std::pair<size_t, void *> zip() {
        size_t size = sizeof(int) * 3;
        size_t i = 0;
        while (i < _data.size()) {
            auto blockValue = _data[i];
            while (i < _data.size() && _data[i] == blockValue)
                i++;
            size += sizeof(CompressionCounterType) + sizeof(T);
        }
        CompressionCounterType blockSize;
        void *raw = new unsigned char[size];
        auto coords = static_cast<int *>(raw);
        coords[0] = _x;
        coords[1] = _y;
        coords[2] = _z;
        unsigned char *data = ((unsigned char *) raw) + sizeof(int) * 3;
        i = 0;
        while (i < _data.size()) {
            blockSize = 0;
            auto blockValue = _data[i];
            while (i < _data.size() && _data[i] == blockValue) {
                blockSize++;
                i++;
            }
            *((CompressionCounterType *) data) = blockSize;
            *((T *) (data + sizeof(CompressionCounterType))) = blockValue;
            data = data + sizeof(CompressionCounterType) + sizeof(T);
        }
        spdlog::info("Zipping {} => {} x {} x {}", _data.size(), coords[0], coords[1], coords[2]);
        return std::make_pair(size, raw);
    }

private:
    using CompressionCounterType = unsigned short;
    int _x, _y, _z;
    std::vector<T> _data;
};

#endif //APP_FLAT3DARRAY_HPP
