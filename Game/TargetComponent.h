#pragma once

#include <Constellate.h>

using namespace csl;
class TargetComponent : public Component {
private:
	int someData = 111;

public:
	void init() override {

		auto entity = this->getEntity();
		ColliderComponent* collider = dynamic_cast<ColliderComponent*>(entity->GetComponent(ComponentType::ColliderComponentType));


		collider->SetCollisionCallback([&](ColliderComponent& collidedWithf) {
   
				// Example output
				if (collidedWithf.getEntity()->hasTag("Projectile")) {
					this->getEntity()->MarkForDeletion();
					collidedWithf.getEntity()->MarkForDeletion();
				}

            });
	}

	void printDude() {
		std::cout << someData;
	}

	void update(float mFT) override;

	ComponentType GetComponentType() override {
		return ComponentType::CustomComponentType2;
	}
};