#pragma once

#include "Entity-Component/Components/PhysicsComponent.h"

#include "Entity-Component/Components/Colliders/ShpereCollider.h"

#include "glm.hpp"

namespace csl {

	class PhysicsManager {
	private:
		glm::vec3 gravitationalAcceleration;
	public:
		PhysicsManager();
		void CheckCollisions();
		void CalculatePhysics(float mFT);
	};
}