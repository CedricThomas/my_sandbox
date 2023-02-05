//
// Created by arzad on 20/02/2022.
//

#ifndef APP_CAMERA_HPP
#define APP_CAMERA_HPP

#include "lib/graphics/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <vector>

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
//const float SPEED       =  2.5f;
const float SPEED       =  500.0f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:

    // Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
    enum Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    // constructor with vectors
    explicit Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 getViewMatrix() const;

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void processKeyboard(Movement direction, float deltaTime);

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void processMouseScroll(float yoffset);

    // getters
    const glm::vec3 &getPosition() const;

    float getZoom() const;

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();
    // camera Attributes
    glm::vec3 _position;
    glm::vec3 _front;
    glm::vec3 _up;
    glm::vec3 _right;
    glm::vec3 _worldUp;
    // euler Angles
    float _yaw;
    float _pitch;
    // camera options
    float _movementSpeed;
    float _mouseSensitivity;
    float _zoom;
};

#endif //APP_CAMERA_HPP
