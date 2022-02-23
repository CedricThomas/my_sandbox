//
// Created by arzad on 23/02/2022.
//

#ifndef APP_WORLD_HPP
#define APP_WORLD_HPP

#include "lib/interfaces/Observer.hpp"

class World: public Observer<int>, public Observer<float> {
public:
    void update(int value) override;
    void update(float value) override;
};


#endif //APP_WORLD_HPP
