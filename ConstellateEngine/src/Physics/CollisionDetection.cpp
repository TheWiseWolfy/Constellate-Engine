#pragma once

#include "CollisionDetection.h"

#include "Entity-Component/Components/Colliders/ShpereCollider.h"
#include "Entity-Component/Components/Colliders/PlaneCollider.h"

namespace csl {

	CollisionDetails FindShereAgainstShere(SphereCollider* colliderSphere1, SphereCollider* colliderSphere2) {
		CollisionDetails colDetails;

		// Calculate the distance between the centers of the spheres
		glm::vec3 centerToCenter = colliderSphere2->getPosition() - colliderSphere1->getPosition();
		float distance = glm::length(centerToCenter);

		// Check if the spheres are colliding
		float sumRadii = colliderSphere1->getRadius() + colliderSphere2->getRadius();
		if (distance < sumRadii) {
			colDetails.hasCollided = true;

			// Calculate penetration depth
			colDetails.depth = sumRadii - distance;

			// Calculate the collision normal
			colDetails.normal = glm::normalize(centerToCenter);

			// Calculate the collision point on sphere1
			colDetails.pointA = colliderSphere1->getPosition() + colDetails.normal * colliderSphere1->getRadius();

			// Calculate the collision point on sphere2
			colDetails.pointB = colliderSphere2->getPosition() - colDetails.normal * colliderSphere2->getRadius();
		}
		else {
			colDetails.hasCollided = false;
		}

		return colDetails;
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