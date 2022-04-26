//
// Created by arzad on 16/01/2022.
//

#ifndef APP_ARENDERER_HPP
#define APP_ARENDERER_HPP

#include <string>

class Application;

class ARenderer {
public:
    explicit ARenderer(std::string name);

    virtual void onInit(const Application &application);

    virtual void onInput(const Application &application);

    virtual void onRender(const Application &application);

    virtual void onCleanup(const Application &application);

    virtual void onMouse(const Application &application, double xpos, double ypos);

    virtual void onScroll(const Application &application, double xoffset, double yoffset);

    const std::string &getName() const;

private:
    std::string _name;
};


#endif //APP_ARENDERER_HPP
