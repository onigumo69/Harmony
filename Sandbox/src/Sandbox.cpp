#include "Harmony.h"
#include "Harmony/Core/EntryPoint.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include <string>

#include "Sandbox2D.h"
#include "ExampleLayer.h"

class Sandbox : public Harmony::Application
{
public:
	Sandbox()
	{
		//push_layer(new ExampleLayer());
		push_layer(new Sandbox2D());
	}

	~Sandbox()
	{

	}

};

Harmony::Application* Harmony::create_application()
{
	return new Sandbox();
}