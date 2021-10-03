#pragma once

#include "Core.h"
#include "Event/Event.h"

#include <sstream>

namespace Harmony
{
	class HARMONY_API Layer
	{
	public:
		Layer(const std::string& debug_name = "Layer");
		virtual ~Layer();

		virtual void on_attach() {}
		virtual void on_detach() {}
		virtual void on_update() {}
		virtual void on_event(Event& event) {}

		inline const std::string& get_name() { return _debug_name; }
	protected:
		std::string _debug_name;
	};
}