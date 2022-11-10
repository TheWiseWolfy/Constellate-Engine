#pragma once

#include "cslpch.h"
#include "Layer.h"

namespace csl {
	class LayerStack {
	private:
		std::vector<Layer*> _layers;
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return _layers.begin(); }
		std::vector<Layer*>::iterator end() { return _layers.end(); }
	};
}