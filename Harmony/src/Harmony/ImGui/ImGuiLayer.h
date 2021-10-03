#pragma once

#include "Harmony/Layer.h"

#include "Harmony/Event/ApplicationEvent.h"
#include "Harmony/Event/KeyEvent.h"
#include "Harmony/Event/MouseEvent.h"

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

		// for testing only
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);
	private:
		float _time = 0.0f;
	};

}