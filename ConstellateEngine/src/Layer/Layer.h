#pragma once

#include "cslpch.h"
#include "Events/Event.h"

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