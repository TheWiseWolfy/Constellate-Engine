#pragma once

#include "CollisionDetection.h"

#include "Entity-Component/Components/Colliders/ShpereCollider.h"
#include "Entity-Component/Components/Colliders/PlaneCollider.h"

namespace csl {

	CollisionDetails FindShereAgainstShere(SphereCollider* collider1, SphereCollider* collider2) {
		CollisionDetails wa;
		return wa;
	}

	CollisionDetails FindShereAgainstPlane(SphereCollider* colliderSphere, PlaneColider* colliderPlane) {
		CollisionDetails colDetails;

		// Calculate the distance between the plane and the center of the sphere
		float dist =abs( glm::dot(colliderPlane->getNormal(), colliderPlane->getPosition() - colliderSphere->getPosition()) );

		if (dist < colliderSphere->getRadius()) {
			colDetails.hasCollided = true;

			//Penetration depth
			colDetails.depth = colliderSphere->getRadius() - dist;

			glm::vec3 shpereCenterProjection = colliderPlane->getNormal() * colDetails.depth;
			colDetails.pointA = colliderSphere->getPosition() - shpereCenterProjection;

			//Normal is simple at least :3
			colDetails.normal = colliderPlane->getNormal();

		}
		else {
			colDetails.hasCollided = false;
		}

		return colDetails;
	}


}