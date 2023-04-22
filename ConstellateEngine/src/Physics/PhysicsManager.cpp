
#include "cslpch.h"
#include "PhysicsManager.h"

#include "Core/Application.h"

namespace csl {

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


	PhysicsManager::PhysicsManager() {

		gravitationalAcceleration = glm::vec3(0, -1.9, 0);
	}



	void PhysicsManager::CheckCollisions() {

		/*std::vector<std::unique_ptr<Entity>>& entities = Application::GetInstance().GetEntityManager().GetEntityVector();
		std::vector<ColliderComponent*> coliderComponents;

		for (auto& entity : entities) {
			if (entity->HasComponent(ComponentType::ColliderComponentType)) {
				coliderComponents.push_back((ColliderComponent*)entity->GetComponent(ComponentType::ColliderComponentType));
			}
			aux(entity, coliderComponents);
		}

		for (auto&& component : coliderComponents) {
			Application::GetInstance().GetRenderer().RenderCollider(component);

			for (auto&& other : coliderComponents) {
				if (component == other) continue;

			
			}
		}*/

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

		CheckCollisions();

		for (auto&& component : physicsComponents) {
			component->setAcceleration(component->getAcceleration() + gravitationalAcceleration * mFT);
			component->setVelocity(component->getVelocity() + component->getAcceleration() * mFT);
			auto calculatedPosition = component->getEntity()->getTransform().getPosition() + component->getVelocity() * mFT;
			component->getEntity()->getTransform().setPosition(calculatedPosition);
		}
	}


}