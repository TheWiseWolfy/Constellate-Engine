#pragma once

#include "cslpch.h"

#include "glm.hpp"

#include "Component.h"
#include "Physics/CollisionPrimitives.h"
#include "Entity-Component/Entity.h"

namespace csl {
    
    class SphereCollider;
    class PlaneColider;

    class ColliderComponent : public Component {
    private:

    public:

        ColliderComponent() {

        }

        void update(float mFT) override
        {
        }
        void draw() override
        {
        }

        ComponentType GetComponentType() override {
            return ComponentType::ColliderComponentType;
        }

        //Here is the scary stuff
        virtual CollisionDetails TestCollision(ColliderComponent* collider) = 0;
        virtual CollisionDetails TestCollision(SphereCollider* collider) = 0;
        virtual CollisionDetails TestCollision(PlaneColider* collider) = 0;

    };

}