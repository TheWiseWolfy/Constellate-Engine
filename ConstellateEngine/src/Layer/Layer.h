#pragma once

#include "cslpch.h"
#include "Events/Event.h"


/*
The layer abtraction is a abtraction centered around draw ordering and incapsulating certain logic that in naturally separate: graphics and UI

Any layer pushed into the _layerStack contain in Application will receive updates and events every frame cycle.
*/

namespace csl {
	class Layer {
	protected:
		std::string _debugName;
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach(){}
		virtual void OnDetach(){}
		virtual void OnUpdate(){}
		virtual void OnEvent(EngineEvent& event){}

		const std::string& GetName() const { return  _debugName; }
	};
}