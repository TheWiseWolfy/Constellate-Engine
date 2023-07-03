#include "FirstPersonCamera.h"

float FPCamera::getYaw()
{
	return _yaw;
}

float FPCamera::getPitch()
{
	return _pitch;
}

glm::vec2 FPCamera:: ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch , float mouseSensitivity )
{
	// euler Angles
	xoffset *= mouseSensitivity;
	yoffset *= mouseSensitivity;

	_yaw += xoffset;
	_pitch += yoffset;

	if (constrainPitch)
	{
		if (_pitch > 89.0f)
			_pitch = 89.0f;
		if (_pitch < -89.0f)
			_pitch = -89.0f;
	}

	// update Front, Right and Up Vectors using the updated Euler angles
	return glm::vec2(_yaw, _pitch);
}

glm::vec3 FPCamera::getCameraDirection() {
	glm::vec3 direction;

	direction.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	direction.y = sin(glm::radians(_pitch));
	direction.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));

	return glm::normalize(direction);
}

glm::vec3 FPCamera::getRightVector() {
	glm::vec3 cameraDirection = getCameraDirection();
	return glm::normalize(glm::cross(cameraDirection, glm::vec3(0, 1, 0)));
}