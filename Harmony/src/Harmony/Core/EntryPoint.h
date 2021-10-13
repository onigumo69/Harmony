#pragma once

#include "Harmony/Debug/Instrumentor.h"

extern Harmony::Application* Harmony::create_application();

int main(int argc, char** argv)
{
	Harmony::Log::init();

	HM_PROFILE_BEGIN_SESSION("Startup", "HarmonyProfile-Startup.json");
	auto app = Harmony::create_application();
	HM_PROFILE_END_SESSION();

	HM_PROFILE_BEGIN_SESSION("Runtime", "HarmonyProfile-Runtime.json");
	app->run();
	HM_PROFILE_END_SESSION();

	HM_PROFILE_BEGIN_SESSION("Shutdown", "HarmonyProfile-Shutdown.json");
	delete app;
	HM_PROFILE_END_SESSION();
}