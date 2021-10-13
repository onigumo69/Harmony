#pragma once

#include "Core.h"
#include "Timestep.h"
#include "Harmony/Event/Event.h"

#include <sstream>

namespace Harmony
{
	class Layer
	{
	public:
		Layer(const std::string& debug_name = "Layer");
		virtual ~Layer();

		virtual void on_attach() {}
		virtual void on_detach() {}
		virtual void on_update(Timestep ts) {}
		virtual void on_imgui_render() {}
		virtual void on_event(Event& event) {}

		inline const std::string& get_name() { return _debug_name; }
	protected:
		std::string _debug_name;
	};
}