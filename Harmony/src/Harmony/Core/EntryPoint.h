#pragma once

extern Harmony::Application* Harmony::create_application();

int main(int argc, char** argv)
{
	Harmony::Log::init();

	auto app = Harmony::create_application();
	app->run();
	delete app;
}