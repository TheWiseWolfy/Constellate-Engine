/*
File:PlayerComponent.h

By inheriting the classic component type from Constellate and implementing custom behavious in response to events
We will implement controls for a player entity.




*/
#pragma once

#include <Constellate.h>

#include "FirstPersonCamera.h"

using namespace csl;

class PlayerComponent : public Component {

private:
    FPCamera& _camera;
public:
    PlayerComponent(FPCamera& camera) : _camera(camera){}

    void update(float mFT) override {
        
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

    ComponentType GetComponentType() override {
        return ComponentType::CustomComponentType1;
    }


};