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

        //Here is the scary stuff
        virtual CollisionDetails TestCollision(ColliderComponent* collider) override;
        virtual CollisionDetails TestCollision(SphereCollider* collider) override;
        virtual CollisionDetails TestCollision(PlaneColider* collider) override;

    };

}