#pragma once

#ifdef HARMONY_BUILD_DLL
	#define HARMONY_API __declspec(dllexport)
#else
	#define HARMONY_API __declspec(dllimport)
#endif