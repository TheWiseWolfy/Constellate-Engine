#pragma once

#include "glm.hpp"

#include "Component.h"


namespace csl {

    class PhysicsComponent : public Component {
    private:
        float _mass;
        glm::vec3 _velocity;
        glm::vec3 _acceleration;

    public:

       

        PhysicsComponent() {
            _velocity = glm::vec3(0, 0, 0);
            _acceleration = glm::vec3(0, 0, 0);
            _mass = 1;
        }

        glm::vec3 getVelocity() {
            return _velocity;
        }

        glm::vec3 getAcceleration() {
            return _acceleration;
        }

        void setVelocity(glm::vec3 velocity) {
            _velocity = velocity;
        }
       
        void setAcceleration(glm::vec3 acceleration) {
            _acceleration = acceleration;
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