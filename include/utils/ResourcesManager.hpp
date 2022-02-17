//
// Created by arzad on 22/01/2022.
//

#ifndef APP_RESOURCESMANAGER_HPP
#define APP_RESOURCESMANAGER_HPP

#include <string>

class ResourcesManager {
public:

    explicit ResourcesManager(std::string path);
    std::string getResourcePath(const std::string &resourceName);
private:
    std::string _resourcesPath;
};


#endif //APP_RESOURCESMANAGER_HPP
