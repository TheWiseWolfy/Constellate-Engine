
#include "LayerStack.h"


namespace csl{
	LayerStack::LayerStack()
	{
	}
	LayerStack::~LayerStack()
	{
		for (Layer* layer : _layers) {
			delete layer;
		}
	}
	
	void LayerStack::PushLayer(Layer* layer)
	{
		_layers.emplace_back(layer);
	}
	void LayerStack::PushOverlay(Layer* overlay)
	{
		throw new NotImplementedException();
	}
	void LayerStack::PopLayer(Layer* layer)
	{
		throw new NotImplementedException();
	}
	void LayerStack::PopOverlay(Layer* overlay)
	{
		throw new NotImplementedException();
	}
}