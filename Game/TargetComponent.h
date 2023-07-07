#pragma once

#include <Constellate.h>
#include "TargetHitEvent.h"

using namespace csl;
class TargetComponent : public Component {
private:
	bool _hit =  false;
public:
	void init() override {

		auto entity = this->getEntity();
		ColliderComponent* collider = dynamic_cast<ColliderComponent*>(entity->GetComponent(ComponentType::ColliderComponentType));

		collider->SetCollisionCallback([&](ColliderComponent& collidedWithf) {
   
				// Example output
				if (collidedWithf.getEntity()->hasTag("Projectile")) {
					this->getEntity()->MarkForDeletion();
					
					//TODO Investigate this
					//collidedWithf.getEntity()->MarkForDeletion();

					if (!_hit) { //trusty latch 
						_hit = true;
						TargetHitEvent e;

						Application::GetInstance().PublishEvent(e);
					}
				}

            });
	}


	void update(float mFT) override;

	ComponentType GetComponentType() override {
		return ComponentType::CustomComponentType2;
	}
};