/*
File:PlayerComponent.h

By inheriting the classic component type from Constellate and implementing custom behavious in response to events
We will implement controls for a player entity.




*/
#pragma once

#include <Constellate.h>

using namespace csl;

class PlayerComponent : public Component {
private:

public:

    void update(float mFT) override {
        
        //TODO: Detect that I'm pressing buttons

        if (InputManager::getInstance()->isKeyPressed(CSL_KEY_V)) {
            //Apply forces to the current entity to move the player
            std::cout << "I am pressin.";
        }


        
    }

    ComponentType GetComponentType() override {
        return ComponentType::CustomComponentType1;
    }


};