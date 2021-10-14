#include "LayerStack.h"

namespace Harmony
{

	LayerStack::~LayerStack()
	{
		for (Layer* layer : _layers)
		{
			layer->on_detach();
			delete layer;
		}
	}

	void LayerStack::push_layer(Layer* layer)
	{
		_layers.emplace(_layers.begin() + _layer_insert_index, layer);
		_layer_insert_index++;
	}

	void LayerStack::push_overlay(Layer* overlay)
	{
		_layers.emplace_back(overlay);
	}

	void LayerStack::pop_layer(Layer* layer)
	{
		auto it = std::find(_layers.begin(), _layers.begin() + _layer_insert_index, layer);
		if (it != _layers.begin() + _layer_insert_index)
		{
			layer->on_detach();
			_layers.erase(it);
			_layer_insert_index--;
		}
	}

	void LayerStack::pop_overlay(Layer* overlay)
	{
		auto it = std::find(_layers.begin() + _layer_insert_index, _layers.end(), overlay);
		if (it != _layers.end())
		{
			overlay->on_detach();
			_layers.erase(it);
		}
	}
}