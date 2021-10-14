#pragma once

#include "Harmony/Core/Layer.h"

#include "Harmony/Event/ApplicationEvent.h"
#include "Harmony/Event/KeyEvent.h"
#include "Harmony/Event/MouseEvent.h"

namespace Harmony
{

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void on_attach() override;
		virtual void on_detach() override;
		virtual void on_event(Event& e) override;

		void begin();
		void end();

		void block_events(bool block) { _block_events = block; }
	private:
		bool _block_events = true;
		float _time = 0.0f;
	};

}