#pragma once

#include "Entity-Component/Components/PhysicsComponent.h"

#include "Entity-Component/Components/Colliders/ShpereCollider.h"
#include "Entity-Component/Components/Colliders/PlaneCollider.h"

#include "glm.hpp"

namespace csl {

	class PhysicsManager {
	private:
		glm::vec3 _gravitationalAcceleration;

		void detectCollisions();
		void solveCollision(Collision collision);

		bool _gravity = true;
	public:
		PhysicsManager();
		void calculatePhysics(float mFT);

		void setGravity(bool gravity){
			_gravity = gravity;
		}
	};
}