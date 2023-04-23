
#include "ShpereCollider.h"

#include "Physics/CollisionDetection.h"

namespace csl {

    //Example of double dispach 
    CollisionDetails SphereCollider::TestCollision(ColliderComponent* collider) {
        return collider->TestCollision(this);
    }

    CollisionDetails SphereCollider::TestCollision(SphereCollider* collider) {
       
        return FindShereAgainstShere(this, collider);;
    }
    CollisionDetails SphereCollider::TestCollision(PlaneColider* collider) {
        return FindShereAgainstPlane(this, collider);
    }

}