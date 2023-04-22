#pragma once

#include "CollisionPrimitives.h"

#include "Entity-Component/Components/Colliders/ShpereCollider.h"
#include "Entity-Component/Components/Colliders/PlaneCollider.h"

namespace csl {

	CollisionDetails FindShereAgainstShere(SphereCollider* collider1, SphereCollider* collider2){
		CollisionDetails wa;
		return wa;
	}

	CollisionDetails FindShereAgainstPlane(SphereCollider* collider1, PlaneColider* collider2){
		CollisionDetails wa;
		return wa;
	}

}