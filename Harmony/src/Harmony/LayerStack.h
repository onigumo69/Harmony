#pragma once

#include "Core.h"
#include "Layer.h"

#include <vector>

namespace Harmony
{
	
	class HARMONY_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void push_layer(Layer* layer);
		void push_overlay(Layer* overlay);
		void pop_layer(Layer* layer);
		void pop_overlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return _layers.begin(); }
		std::vector<Layer*>::iterator end() { return _layers.end(); }
	private:
		std::vector<Layer*> _layers;
		std::vector<Layer*>::iterator _layer_insert;
	};

}
