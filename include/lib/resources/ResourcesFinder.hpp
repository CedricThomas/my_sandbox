//
// Created by arzad on 22/01/2022.
//

#ifndef APP_RESOURCESFINDER_HPP
#define APP_RESOURCESFINDER_HPP

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>
#include "Resource.hpp"

#define TEXTURES_FOLDER "textures"
#define BLOCKS_FOLDER "block"
#define ENTITIES_FOLDER "entity"
#define ITEMS_FOLDER "item"

#define SHADERS_FOLDER "shaders"

class ResourcesFinder {
public:
    static void root(const std::string &path);
    explicit ResourcesFinder(std::string path = "");
    ResourcesFinder append(const std::string &path);
    Resource get();
    std::vector<Resource> list();
private:
    static std::string _root;
    std::string _path;
};


#endif //APP_RESOURCESFINDER_HPP
