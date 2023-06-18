#pragma once

#include "glm.hpp"

class FPCamera {
private:
	float _yaw = 0;
	float _pitch = 0;

public:
	float getYaw();
	float getPitch();

	glm::vec2 ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true, float mouseSensitivity = 0.1f);

	glm::vec3 getCameraDirection();
	glm::vec3 getRightVector();
};