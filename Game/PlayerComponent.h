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

    void update(float mFT) override;

    ComponentType GetComponentType() override {
        return ComponentType::CustomComponentType1;
    }
};