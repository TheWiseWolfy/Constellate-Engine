#pragma once

#include "glm/glm.hpp"


#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <vector>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 10.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
private:
    // euler Angles
    float _yaw;
    float _pitch;
    // camera options
    float _movementSpeed;
    float _mouseSensitivity;
    float _zoom;

    glm::vec3 _position;
    const glm::vec3 _cameraUp;

    // camera Attributes
    glm::vec3 _front;
    glm::vec3 _up;
    glm::vec3 _right;

public:
 
    // constructor with vectors
    Camera(glm::vec3 position , glm::vec3 up , float yaw , float pitch ) : 
        _position(position),
        _cameraUp(up),
        _yaw(yaw),
        _pitch(pitch),

        _movementSpeed(SPEED),
        _mouseSensitivity(SENSITIVITY),
        _zoom(ZOOM)
    {
    }

    glm::vec3 GetPostion() {
        return _position;
    }


    void SetPosition(glm::vec3 position) {
        _position = position;
    }

    void SetRotation(glm::vec2 rotation) {
        _yaw = rotation.x;
        _pitch = rotation.y;
    }

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()
    {
        updateCameraVectors();
        return glm::lookAt(_position, _position + _front, _up);
    }

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors()
    {
        // calculate the new Front vector
        glm::vec3 front;

        front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
        front.y = sin(glm::radians(_pitch));
        front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));

        // also re-calculate the Right and Up vector
        // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        _front = glm::normalize(front);
        _right = glm::normalize(glm::cross(_front, _cameraUp));  
        _up = glm::normalize(glm::cross(_right, _front));
    }
};
