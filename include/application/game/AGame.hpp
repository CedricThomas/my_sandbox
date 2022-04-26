//
// Created by arzad on 26/04/2022.
//

#ifndef APP_AGAME_HPP
#define APP_AGAME_HPP

#include <memory>
#include "Camera.hpp"
#include "GLFW/glfw3.h"
#include "application/Application.hpp"
#include "application/game/renderer/RenderingTracker.hpp"

class AGame {
public:
    explicit AGame(std::shared_ptr<Application> application);

    virtual void onInit() = 0;

    virtual void onInput() = 0;

    virtual void onRender();

    virtual void onCleanup() = 0;

    virtual void onMouseMove(double xpos, double ypos);

    virtual void onScroll(double xoffset, double yoffset) = 0;

    virtual const Camera &getCamera() const;

    virtual const Application::ApplicationConfig &getConfig();

    virtual GLFWwindow *getWindow();

    const RenderingTracker &getTracker();


protected:
    std::shared_ptr<Application> _application;
    RenderingTracker _tracker;
    Camera _camera;

};


#endif //APP_AGAME_HPP
