#pragma once

#include <assimp/scene.h>

#include "cslpch.h"

#include "glm.hpp"
#include "Component.h"
#include "Physics/CollisionPrimitives.h"
#include "Entity-Component/Entity.h"

namespace csl {
    
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
    };

}