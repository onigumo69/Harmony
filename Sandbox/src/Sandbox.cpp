#include <Harmony.h>

class ExampleLayer : public Harmony::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void on_update() override
	{
		if(Harmony::Input::is_key_pressed(HM_KEY_TAB))
			HM_TRACE("Tab key is pressed (poll)!");
	}

	void on_event(Harmony::Event& event) override
	{
		if (event.get_event_type() == Harmony::EventType::KeyPressed)
		{
			Harmony::KeyPressedEvent& e = (Harmony::KeyPressedEvent&)event;
			if (e.get_keycode() == HM_KEY_TAB)
				HM_TRACE("Tab key is pressed (event)!");
			HM_TRACE("{0}", (char)e.get_keycode());
		}
	}

};

class Sandbox : public Harmony::Application
{
public:
	Sandbox()
	{
		push_layer(new ExampleLayer());
		push_layer(new Harmony::ImGuiLayer());
	}

	~Sandbox()
	{

	}

};

Harmony::Application* Harmony::create_application()
{
	return new Sandbox();
}