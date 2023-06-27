#include "TargetComponent.h"



void TargetComponent::update(float mFT) {

	glm::vec3 currentRotation = this->getEntity()->GetRotation();

	currentRotation = currentRotation + (glm::vec3(0.0f, 0.5f, 0.0f) * mFT);

	this->getEntity()->SetRotation(currentRotation);

	return;

}
