#pragma once

#include "Harmony/Layer.h"

namespace Harmony {

	class HARMONY_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void on_attach();
		void on_detach();
		void on_update();
		void on_event(Event& event);
	private:
		float _time = 0.0f;
	};

}