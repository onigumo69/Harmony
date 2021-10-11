#pragma once

#include "Harmony/Core/Layer.h"

#include "Harmony/Event/ApplicationEvent.h"
#include "Harmony/Event/KeyEvent.h"
#include "Harmony/Event/MouseEvent.h"

namespace Harmony
{

	class HARMONY_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void on_attach() override;
		virtual void on_detach() override;
		virtual void on_imgui_render() override;

		void begin();
		void end();
	private:
		float _time = 0.0f;
	};

}