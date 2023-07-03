#pragma once

#include "cslpch.h"

#include "glm.hpp"

#include "Component.h"
#include "Physics/CollisionPrimitives.h"
#include "Entity-Component/Entity.h"
#include "Core/Log.h"


namespace csl {
    
    class SphereCollider;
    class PlaneColider;

    class ColliderComponent : public Component {
    private:
        using CollisionCallback = std::function<void(ColliderComponent&)>;
        CollisionCallback collisionCallback;

    public:

        ColliderComponent() {

        }

        void update(float mFT) override
        {
        }

        void SetCollisionCallback(CollisionCallback callback) {
            collisionCallback = std::move(callback);
        }

        void OnCollision(ColliderComponent& collidedWith) {
            if (collisionCallback) {
                collisionCallback(collidedWith);
            }
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