#pragma once

#include "glm.hpp"

#include "Component.h"


namespace csl {

    class PhysicsComponent : public Component {
    private:
       

    public:

        glm::vec3 velocity;
        glm::vec3 acceleration;

        PhysicsComponent() {
            velocity = glm::vec3(0, 0, 0);
            acceleration = glm::vec3(0, 0, 0);
        }



       
        void update(float mFT) override
        {

        }
        void draw() override
        {
        }



        ComponentType GetComponentType() override {
            return ComponentType::PhysicsComponentType;
        }
    };

}