//
// Created by arzad on 20/02/2022.
//

#ifndef APP_FLAT3DARRAY_HPP
#define APP_FLAT3DARRAY_HPP

#include <vector>

template<typename T>
class Flat3DArray {
public:
    Flat3DArray(int x, int y, int z) : _x(x), _y(y), _z(z) {
        _data.resize(x * y * z);
    }

    ~Flat3DArray() = default;

    int get(int x, int y, int z) {
        return _data[x + _x * (y + _y * z)];
    }

    void set(int x, int y, int z, T value) {
        _data[x + _x * (y + _y * z)] = value;
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

private:
    int _x, _y, _z;
    std::vector<T> _data;
};

#endif //APP_FLAT3DARRAY_HPP
