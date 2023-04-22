
#include "PlaneCollider.h"
#include "Physics/CollisionDetection.h"

namespace csl {

    //Example of double dispach 
    CollisionDetails PlaneColider::TestCollision(ColliderComponent* collider) {
        return collider->TestCollision(this);
    }
    CollisionDetails PlaneColider::TestCollision(SphereCollider* collider) {
        return FindShereAgainstPlane(collider, this);

    }
    CollisionDetails PlaneColider::TestCollision(PlaneColider* collider) {
        return CollisionDetails();  //No cliision between planes sadly

    }

}