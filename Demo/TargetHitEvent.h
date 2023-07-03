#pragma once

#include <Events/Event.h>

using namespace csl;

class TargetHitEvent : public EngineEvent {
protected:
public:

	TargetHitEvent()  {}

	const char* GetName() const override {
		return "TargetHitEvent";
	}

	EVENT_CLASS_CATEGORY(EventCategoryCustom1)
	EVENT_TYPE_FUCTIONS(CustomEvent1)

};
