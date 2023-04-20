
#include "cslpch.h"
#include "PhysicsManager.h"

#include "Core/Application.h"

namespace csl {

	//This is an ugly piece of code that sadly has to live on for now
	void aux(std::unique_ptr<Entity>& entity, std::vector<ColliderComponent*>& coliderComponents) {
		auto& childrenEntitys = entity->GetChildren();

		for (auto& entity : childrenEntitys) {
			if (entity->HasComponent(ComponentType::ColliderComponentType)) {
				coliderComponents.push_back((ColliderComponent*)entity->GetComponent(ComponentType::GraphicsComponentType));
			}
			aux(entity, coliderComponents);
		}

	}


	void PhysicsManager::CheckCollisions() {

		std::vector<std::unique_ptr<Entity>>& entities = Application::GetInstance().GetEntityManager().GetEntityVector();
		std::vector<ColliderComponent*> coliderComponents;

		for (auto& entity : entities) {
			if (entity->HasComponent(ComponentType::ColliderComponentType)) {
				coliderComponents.push_back((ColliderComponent*)entity->GetComponent(ComponentType::ColliderComponentType));
			}
			aux(entity, coliderComponents);
		}


		for (auto&& component : coliderComponents) {


			Application::GetInstance().GetRenderer().RenderCollider(component);


		}
	}
}