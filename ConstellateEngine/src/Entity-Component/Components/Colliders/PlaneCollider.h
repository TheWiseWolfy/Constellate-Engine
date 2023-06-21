#pragma once

#include "cslpch.h"

#include "glm.hpp"

#include "Entity-Component/Components/ColliderComponent.h"
#include "Physics/CollisionPrimitives.h"

namespace csl {

    class PlaneColider : public ColliderComponent {
    private:
    public:

        PlaneColider() {
        }

        void update(float mFT) override
        {
        }
        void draw() override
        {
        }

        glm::vec3 getNormal() {
            glm::vec3 vec = this->getEntity()->getTransform().getUpVector();
            return vec;
        };
        

        glm::vec3 getPosition() {
            return this->getEntity()->getAbsolutePosition();
        }

        //Here is the scary stuff
        virtual CollisionDetails TestCollision(ColliderComponent* collider) override;
        virtual CollisionDetails TestCollision(SphereCollider* collider) override;
        virtual CollisionDetails TestCollision(PlaneColider* collider) override;

    };

}