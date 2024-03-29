
#include "cslpch.h"
#include "PhysicsManager.h"

#include "Core/Application.h"

namespace csl {

	PhysicsManager::PhysicsManager() {
		_gravitationalAcceleration = glm::vec3(0, -9.2, 0);
	}

	//This is an ugly piece of code that sadly has to live on for now
	void aux(std::unique_ptr<Entity>& entity, std::vector<PhysicsComponent*>& physicsComponents) {
		auto& childrenEntitys = entity->GetChildren();

		for (auto& entity : childrenEntitys) {
			if (entity->HasComponent(ComponentType::PhysicsComponentType)) {
				physicsComponents.push_back((PhysicsComponent*)entity->GetComponent(ComponentType::PhysicsComponentType));
			}
			aux(entity, physicsComponents);
		}

	}

	//This is an ugly piece of code that sadly has to live on for now
	void aux2(std::unique_ptr<Entity>& entity, std::vector<ColliderComponent*>& colliderComponents) {
		auto& childrenEntitys = entity->GetChildren();

		for (auto& entity : childrenEntitys) {
			if (entity->HasComponent(ComponentType::ColliderComponentType)) {
				colliderComponents.push_back((ColliderComponent*)entity->GetComponent(ComponentType::ColliderComponentType));
			}
			aux2(entity, colliderComponents);
		}
	}

	void PhysicsManager::solveCollision(Collision collision) {

		// Get the two collider components involved in the collision
		ColliderComponent* objectA = collision.objectA;
		ColliderComponent* objectB = collision.objectB;

		PhysicsComponent* rigidbodyA = (PhysicsComponent*)objectA->getEntity()->GetComponent(ComponentType::PhysicsComponentType);
		PhysicsComponent* rigidbodyB = (PhysicsComponent*)objectB->getEntity()->GetComponent(ComponentType::PhysicsComponentType);

		// Get the collision details
		CollisionDetails details = collision.details;

		// Calculate the new velocity and position for each component
		glm::vec3 velA = rigidbodyA->getVelocity();
		glm::vec3 velB = rigidbodyB->getVelocity();

		// Calculate the relative velocity
		glm::vec3 relVel = velA - velB;


		// Calculate the mass of each object
		float massA = rigidbodyA->getMass();
		float massB = rigidbodyB->getMass();

		float e = 0.1f; // Restitution coefficient (set to 0.1 for example purposes)
		float impulse = (-(1.0f + e) * glm::dot(relVel, details.normal)) / (1.0f / massA + 1.0f / massB);

		// Calculate the total mass
		float totalMass = massA + massB;

		// Calculate the forces of the collision
		velA += impulse / massA * details.normal;
		velB -= impulse / massB * details.normal;


		// Calculate the new positions
		glm::vec3 newPosA = objectA->getEntity()->getTransform().getPosition() + details.normal * (details.depth / totalMass) * massB;
		glm::vec3 newPosB = objectB->getEntity()->getTransform().getPosition() - details.normal * (details.depth / totalMass) * massA;

		// Set the new velocities and positions for each component

		if (!rigidbodyA->getStatic()) {

			rigidbodyA->setVelocity(velA);
			rigidbodyB->applyForce(rigidbodyB->getAcceleration() * -0.1f);
			objectA->getEntity()->getTransform().setPosition(newPosA);
		}

		if (!rigidbodyB->getStatic()) {

			rigidbodyB->setVelocity(velB);
			rigidbodyB->setAcceleration(rigidbodyA->getAcceleration() * -0.1f);
			objectB->getEntity()->getTransform().setPosition(newPosB);
		}


	}


	void PhysicsManager::detectCollisions() {

		std::vector<std::unique_ptr<Entity>>& entities = Application::GetInstance().GetEntityManager().GetEntityVector();
		std::vector<ColliderComponent*> coliderComponents;

		for (auto& entity : entities) {
			if (entity->HasComponent(ComponentType::ColliderComponentType)) {
				coliderComponents.push_back((ColliderComponent*)entity->GetComponent(ComponentType::ColliderComponentType));
			}
			aux2(entity, coliderComponents);
		}

		for (auto& component : coliderComponents) {
			//Application::GetInstance().GetRenderer().RenderCollider(component);

			for (auto& other : coliderComponents) {
				if (component == other) continue;

				CollisionDetails details = component->TestCollision(other);
				
				if (details.hasCollided) {

					//Call the appropiate callbacks
					component->OnCollision(*other);
					other->OnCollision(*component);

					Collision myCollision;

					// Then you can assign values to its members like this:
					myCollision.objectA = component;
					myCollision.objectB = other;
					myCollision.details = details;


					solveCollision(myCollision);
				}
			}
		}
	}

	

	void PhysicsManager::calculatePhysics(float dt) {

		std::vector<std::unique_ptr<Entity>>& entities = Application::GetInstance().GetEntityManager().GetEntityVector();
		std::vector<PhysicsComponent*> physicsComponents;

		for (auto& entity : entities) {
			if (entity->HasComponent(ComponentType::PhysicsComponentType)) {
				physicsComponents.push_back((PhysicsComponent*)entity->GetComponent(ComponentType::PhysicsComponentType));
			}
			aux(entity, physicsComponents);
		}


		for (auto&& component : physicsComponents) {

			if (!component->getStatic()) {

				auto calculatedPosition = component->getEntity()->getTransform().getPosition() + component->getVelocity() * dt;
				component->getEntity()->getTransform().setPosition(calculatedPosition);

				glm::vec3 velA = component->getVelocity() + component->getAcceleration() * dt;

		
				//Simple drag force to slow things down
				velA -= velA * 0.95f * dt;

				if (velA.length() < 0.01f) {
					velA = glm::vec3(0, 0, 0);
				}
				
				component->setVelocity(velA);

				if (_gravity) {
					component->setAcceleration(component->getAcceleration() + _gravitationalAcceleration * dt);
				}
				// Calculate the contribution of friction.
			}
		}

		detectCollisions();

		
	}


}