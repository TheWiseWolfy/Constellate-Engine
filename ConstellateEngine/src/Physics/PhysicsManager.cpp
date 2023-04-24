
#include "cslpch.h"
#include "PhysicsManager.h"

#include "Core/Application.h"

namespace csl {

	PhysicsManager::PhysicsManager() {
		gravitationalAcceleration = glm::vec3(0, -9.2, 0);
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



	std::vector<Collision> PhysicsManager::CheckCollisions() {

		std::vector<Collision> collisions;
		std::vector<std::unique_ptr<Entity>>& entities = Application::GetInstance().GetEntityManager().GetEntityVector();
		std::vector<ColliderComponent*> coliderComponents;

		for (auto& entity : entities) {
			if (entity->HasComponent(ComponentType::ColliderComponentType)) {
				coliderComponents.push_back((ColliderComponent*)entity->GetComponent(ComponentType::ColliderComponentType));
			}
			aux2(entity, coliderComponents);
		}

		for (auto&& component : coliderComponents) {
			//Application::GetInstance().GetRenderer().RenderCollider(component);

			for (auto&& other : coliderComponents) {
				if (component == other) continue;

				CollisionDetails details = component->TestCollision(other);
				
				if (details.hasCollided) {
					//std::cout << "WOW";

					Collision myCollision;

					// Then you can assign values to its members like this:

					myCollision.objectA = component;
					myCollision.objectB = other;
					myCollision.details = details;

					collisions.push_back(myCollision);
				}
			}
		}

		return collisions;
	}

	void solveCollisions(std::vector<Collision>& collisions) {

		for (auto&& collision : collisions) {
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

			// Calculate the impulse
			float impulse = -1.0f * glm::dot(relVel, details.normal);

			// Calculate the mass of each object
			float massA = rigidbodyA->getMass();
			float massB = rigidbodyB->getMass();

			// Calculate the total mass
			float totalMass = massA + massB;

			// Calculate the new velocities
			velA += impulse / massA * details.normal;
			velB -= impulse / massB * details.normal;

			// Calculate the new positions
			glm::vec3 newPosA = objectA->getEntity()->getTransform().getPosition() + details.normal * (details.depth / totalMass) * massB;
			glm::vec3 newPosB = objectB->getEntity()->getTransform().getPosition() - details.normal * (details.depth / totalMass) * massA;

			// Set the new velocities and positions for each component

			if (!rigidbodyA->getStatic()) {

				rigidbodyA->setVelocity(velA);
				objectA->getEntity()->getTransform().setPosition(newPosA);
			}

			if (!rigidbodyB->getStatic()) {

				rigidbodyA->setVelocity(velB);
				objectB->getEntity()->getTransform().setPosition(newPosB);
			}
		
		}

	}


	void PhysicsManager::CalculatePhysics(float mFT) {

		std::vector<std::unique_ptr<Entity>>& entities = Application::GetInstance().GetEntityManager().GetEntityVector();
		std::vector<PhysicsComponent*> physicsComponents;

		for (auto& entity : entities) {
			if (entity->HasComponent(ComponentType::PhysicsComponentType)) {
				physicsComponents.push_back((PhysicsComponent*)entity->GetComponent(ComponentType::PhysicsComponentType));
			}
			aux(entity, physicsComponents);
		}

		auto collisions = CheckCollisions();

		if (collisions.size() != 0) {
			solveCollisions(collisions);
		}

		for (auto&& component : physicsComponents) {

			if (!component->getStatic()) {
				component->setAcceleration(component->getAcceleration() + gravitationalAcceleration * mFT);
				component->setVelocity(component->getVelocity() + component->getAcceleration() * mFT);
				auto calculatedPosition = component->getEntity()->getTransform().getPosition() + component->getVelocity() * mFT;
				component->getEntity()->getTransform().setPosition(calculatedPosition);
			}
		}
		
	}


}