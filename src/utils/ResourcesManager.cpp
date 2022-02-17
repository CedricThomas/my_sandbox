//
// Created by arzad on 22/01/2022.
//

#include <filesystem>
#include <utility>
#include "utils/ResourcesManager.hpp"

ResourcesManager::ResourcesManager(std::string path) : _resourcesPath(std::move(path)) {
}

std::string ResourcesManager::getResourcePath(const std::string &resourceName) {
    std::filesystem::path path(_resourcesPath);
    path.append(resourceName);
    return path.string();
}

