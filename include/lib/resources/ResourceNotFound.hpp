//
// Created by arzad on 09/04/2022.
//

#ifndef APP_RESOURCENOTFOUND_HPP
#define APP_RESOURCENOTFOUND_HPP


#include <stdexcept>

class ResourceNotFound : public std::runtime_error {
public:
    ResourceNotFound(const std::string &msg) : std::runtime_error(msg) {}
};


#endif //APP_RESOURCENOTFOUND_HPP
