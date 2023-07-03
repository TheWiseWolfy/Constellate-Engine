#pragma once

#include "cslpch.h"

#include "glm.hpp"

#include "Entity-Component/Components/ColliderComponent.h"
#include "Physics/CollisionPrimitives.h"

namespace csl {

    class SphereCollider : public ColliderComponent {
    private:
        float _radius;
    public:

        SphereCollider(float radius ) {
            _radius = radius;
        }

        void update(float mFT) override
        {
        }

        float getRadius() {
            return _radius;
        }

        glm::vec3 getPosition() {
            return this->getEntity()->getAbsolutePosition();
        }

        //Here is the scary stuff
        virtual CollisionDetails TestCollision(ColliderComponent* collider) override;
        virtual CollisionDetails TestCollision(SphereCollider* collider) override;
        virtual CollisionDetails TestCollision(PlaneColider* collider) override;

    };

}