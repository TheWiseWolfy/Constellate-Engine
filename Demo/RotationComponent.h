#pragma once

#include <Constellate.h>
#include "TargetHitEvent.h"

using namespace csl;
class RotationComponent : public Component {
private:
	bool hit =  false;
public:
	void init() override {
	}


	void update(float mFT) override;

	ComponentType GetComponentType() override {
		return ComponentType::CustomComponentType3;
	}
};