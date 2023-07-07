#include "RotationComponent.h"


void RotationComponent::update(float mFT) {

	glm::vec3 currentRotation = this->getEntity()->GetRotation();

	currentRotation = currentRotation + (glm::vec3(0.0f, 0.0f, 0.5f) * mFT);

	this->getEntity()->SetRotation(currentRotation);

	return;

}
