#include "PlayerComponent.h"

void PlayerComponent::update(float mFT) {

    //TODO: Detect that I'm pressing buttons
    if (InputManager::getInstance()->isKeyPressed(CSL_KEY_V)) {
        //Get Camera vector
        auto cameraDirection = _camera.getCameraDirection();
        //Get physics component from current entity


        PhysicsComponent* phycomp = dynamic_cast<PhysicsComponent*>(this->getEntity()->GetComponent(ComponentType::PhysicsComponentType));

        if (phycomp) {
            // The cast was successful, phycomp is now a valid pointer to PhysicsComponent
            phycomp->applyForce(glm::vec3(0.0, 0.5, 0.0));
        }
        else {
            // The cast was unsuccessful, phycomp is nullptr
        }
    }
}