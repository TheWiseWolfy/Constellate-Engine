#include "PlayerComponent.h"

void PlayerComponent::update(float mFT) {

    //TODO: Detect that I'm pressing buttons
    if (false) {
        //Get Camera vector
        auto cameraDirection = _camera.getCameraDirection();


    }
}

void PlayerComponent::receiveEvent(EngineEvent& e) {

    EventDispatcher dispatcher(e);

    dispatcher.Dispach<KeyPressedEvent>(std::bind(&PlayerComponent::OnKeyPressed, this, std::placeholders::_1));
}


bool PlayerComponent::OnKeyPressed(KeyPressedEvent& e) {
    PhysicsComponent* phycomp = dynamic_cast<PhysicsComponent*>(this->getEntity()->GetComponent(ComponentType::PhysicsComponentType));

    if (phycomp) {
        if (e.GetKeyCode() == CSL_KEY_V && e.GetAction() == CSL_PRESS) {

            // The cast was successful, phycomp is now a valid pointer to PhysicsComponent
            //phycomp->applyForce(glm::vec3(0.0, 5, 0.0));
            phycomp->zeroVelocity();
        }
        if (e.GetKeyCode() == CSL_KEY_SPACE && e.GetAction() == CSL_PRESS) {

            // The cast was successful, phycomp is now a valid pointer to PhysicsComponent
            phycomp->applyForce(glm::vec3(0.0, 5, 0.0));
        }
    }
    else {
        // The cast was unsuccessful, phycomp is nullptr
        return false;
    }
    return true;
}