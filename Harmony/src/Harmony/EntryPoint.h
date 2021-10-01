#pragma once

extern Harmony::Application* Harmony::create_application();

int main(int argc, char** argv)
{
	Harmony::Log::init();
	HM_CORE_WARN("init Log!");
	int code = 1024;
	HM_INFO("code is {0}", code);

	auto app = Harmony::create_application();
	app->run();
	delete app;
}