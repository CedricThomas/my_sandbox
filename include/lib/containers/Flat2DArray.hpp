//
// Created by arzad on 20/02/2022.
//

#ifndef APP_FLAT2DARRAY_HPP
#define APP_FLAT2DARRAY_HPP

#include <vector>

template<typename T>
class Flat2DArray {
public:
    Flat2DArray(int x, int y) : _x(x), _y(y) {
        _data.resize(x * y);
    }

    ~Flat2DArray() = default;

    int get(int x, int y) {
        return _data[x + _x * y];
    }

    void set(int x, int y, T value) {
        _data[x + _x * y] = value;
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

    const std::vector<T> &getData() const {
        return _data;
    }

private:
    int _x, _y;
    std::vector<T> _data;
};

#endif //APP_FLAT2DARRAY_HPP
