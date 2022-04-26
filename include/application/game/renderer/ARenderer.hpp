//
// Created by arzad on 16/01/2022.
//

#ifndef APP_ARENDERER_HPP
#define APP_ARENDERER_HPP

#include <string>

class AGame;
class ARenderer {
public:
    explicit ARenderer(std::string name);

    virtual void render(AGame &game) = 0;

    const std::string &getName() const;

private:
    std::string _name;
};


#endif //APP_ARENDERER_HPP
