//
// Created by arzad on 22/01/2022.
//

#include <filesystem>
#include <utility>
#include "lib/resources/ResourcesFinder.hpp"
#include "lib/resources/ResourceNotFound.hpp"

std::string ResourcesFinder::_root;

void ResourcesFinder::root(const std::string &path) {
    _root = path;
}

ResourcesFinder ResourcesFinder::append(const std::string &path) {
    std::filesystem::path newPath(_path);
    ResourcesFinder copy = *this;
    newPath.append(path);
    copy._path = newPath;
    return copy;
}

ResourcesFinder::ResourcesFinder(std::string path) : _path(std::move(path)) {}

Resource ResourcesFinder::get() {
    auto rootedPath = std::filesystem::path(_root);
    rootedPath.append(_path);
    if (!std::filesystem::exists(rootedPath)) {
        throw ResourceNotFound(rootedPath);
    }
    return {
            rootedPath.string(),
            rootedPath.extension(),
            rootedPath.stem(),
            rootedPath.filename()
    };
}

std::vector<Resource> ResourcesFinder::list() {
    auto rootedPath = std::filesystem::path(_root);
    rootedPath.append(_path);

    if (!std::filesystem::exists(rootedPath)) {
        throw ResourceNotFound(rootedPath);
    }
    std::vector<Resource> resources;
    for (const auto &entry: std::filesystem::directory_iterator(rootedPath)) {
        std::filesystem::path path(entry.path());
        resources.push_back({
                                    path.string(),
                                    path.extension(),
                                    path.stem(),
                                    path.filename()
                            });
    }

    return resources;
}
