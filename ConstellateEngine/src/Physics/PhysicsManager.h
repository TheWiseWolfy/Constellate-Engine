



#pragma once

#include "Entity-Component/Components/PhysicsComponent.h"

#include "Entity-Component/Components/Colliders/ShpereCollider.h"
#include "Entity-Component/Components/Colliders/PlaneCollider.h"

#include "glm.hpp"

namespace csl {

	class PhysicsManager {
	private:
		glm::vec3 _gravitationalAcceleration;
	public:
		PhysicsManager();
		std::vector<Collision> CheckCollisions();
		void CalculatePhysics(float mFT);
	};
}