#pragma once

#include "CollisionPrimitives.h"

namespace csl {

	class SphereCollider;
	class PlaneColider;

	CollisionDetails FindShereAgainstShere(SphereCollider* collider1, SphereCollider* collider2);
	CollisionDetails FindShereAgainstPlane(SphereCollider* colliderSphere, PlaneColider* colliderPlane);

}