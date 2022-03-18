//
// Created by arzad on 26/02/2022.
//

#ifndef APP_RENDERINGTRACKER_HPP
#define APP_RENDERINGTRACKER_HPP


class RenderingTracker {
public:
    RenderingTracker();
    void trackMousePosition(float x, float y);
    void trackFrameTime(float time);
    const float getFrameDelta() const;
    const float getMouseXDelta() const;
    const float getMouseYDelta() const;
private:
    bool _firstFrame;
    bool _firstMouse;
    float _lastMouseX;
    float _lastMouseY;
    float _currentMouseX;
    float _currentMouseY;
    float _lastFrameTime;
    float _currentFrameTime;
};


#endif //APP_RENDERINGTRACKER_HPP
