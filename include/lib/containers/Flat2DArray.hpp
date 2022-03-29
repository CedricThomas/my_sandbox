//
// Created by arzad on 20/02/2022.
//

#ifndef APP_FLAT2DARRAY_HPP
#define APP_FLAT2DARRAY_HPP

#include <vector>
#include <stdexcept>

template<typename T>
class Flat2DArray {
public:
    Flat2DArray(std::vector<T> data, int x, int y) : _x(x), _y(y), _data(data) {}

    Flat2DArray(int x, int y) : _x(x), _y(y) {
        _data.resize(x * y);
    }

    ~Flat2DArray() = default;

    T get(int x, int y) const {
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
    static Flat2DArray<T> unzip(void *data, int x, int y) {
        std::vector<T> newData(x * y);
        auto size = 0;
        auto begin = newData.begin();

        while (size < x * y) {
            auto block = *((short *) data);
            auto value = *((T *) (static_cast<char*>(data) + sizeof(short)));
            if (size + block >= x * y) {
                throw std::runtime_error("Invalid unzip");
            }
            std::fill(begin, begin + block, value);
            begin += block;
            size += block;
            data = static_cast<char*>(data) + sizeof(short) + sizeof(T);
        }
        return Flat2DArray<T>(newData, x, y);
    }

private:
    int _x, _y;
    std::vector<T> _data;
};

#endif //APP_FLAT2DARRAY_HPP
