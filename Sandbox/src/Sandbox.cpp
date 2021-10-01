#include <Harmony.h>

class Sandbox : public Harmony::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}

};

Harmony::Application* Harmony::create_application()
{
	return new Sandbox();
}