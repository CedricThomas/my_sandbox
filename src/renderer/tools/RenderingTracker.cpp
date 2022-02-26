//
// Created by arzad on 26/02/2022.
//

#include "renderer/tools/RenderingTracker.hpp"

RenderingTracker::RenderingTracker() : _firstFrame(true),
                                       _firstMouse(true),
                                       _lastMouseX(0),
                                       _lastMouseY(0),
                                       _currentMouseX(0),
                                       _currentMouseY(0),
                                       _lastFrameTime(0),
                                       _currentFrameTime(0) {}

void RenderingTracker::trackMousePosition(float x, float y) {
    if (_firstMouse) {
        _currentMouseX = x;
        _currentMouseY = y;
        _firstMouse = false;
    }
    _lastMouseX = _currentMouseX;
    _lastMouseY = _currentMouseY;
    _currentMouseX = x;
    _currentMouseY = y;
}

void RenderingTracker::trackFrameTime(float time) {
    if (_firstFrame) {
        _currentFrameTime = time;
        _firstFrame = false;
    }
    _lastFrameTime = _currentFrameTime;
    _currentFrameTime = time;
}

const float RenderingTracker::getFrameDelta() const {
    if (_firstFrame) {
        return 0;
    } else {
        return _currentFrameTime - _lastFrameTime;
    }
}

const float RenderingTracker::getMouseXDelta() const {
    if (_firstMouse) {
        return 0;
    } else {
        return _currentMouseX - _lastMouseX;
    }
}

const float RenderingTracker::getMouseYDelta() {
    if (_firstMouse) {
        return 0;
    } else {
        return _lastMouseY - _currentMouseY;
    }
}
