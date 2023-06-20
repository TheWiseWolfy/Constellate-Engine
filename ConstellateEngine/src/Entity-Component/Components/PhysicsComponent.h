#pragma once

#include "glm.hpp"

#include "Component.h"


namespace csl {

    class PhysicsComponent : public Component {
    private:
        float _mass;
        glm::vec3 _velocity;
        glm::vec3 _acceleration;
        bool _staticObject;
    public:

        PhysicsComponent() {
            _velocity = glm::vec3(0, 0, 0);
            _acceleration = glm::vec3(0, 0, 0);
            _mass = 1;
            _staticObject = false;
        }

        //Adding force 
        void applyForce(const glm::vec3& force) {
            // Divide the force by mass to get acceleration
            glm::vec3 acceleration = force / _mass;

            // Add the acceleration to the current acceleration
            _acceleration += acceleration;
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

        float getMass() {
            return _mass;
        }

        void setMass(float mass) {
            _mass = mass;
        }

        void setStatic(bool staticObj){
            _staticObject = staticObj;
        }

        bool getStatic() {
            return _staticObject;
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