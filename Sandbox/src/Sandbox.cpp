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
		HM_INFO("ExampleLayer::Update");
	}

	void on_event(Harmony::Event& event) override
	{
		HM_TRACE("{0}", event);
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