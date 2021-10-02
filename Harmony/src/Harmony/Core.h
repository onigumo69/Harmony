#pragma once

#ifdef HARMONY_BUILD_DLL
	#define HARMONY_API __declspec(dllexport)
#else
	#define HARMONY_API __declspec(dllimport)
#endif

#ifdef HM_ENABLE_ASSERTS
	#define HM_ASSERT(x, ...) { if(!(x)) { HM_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define HM_CORE_ASSERT(x, ...) { if(!(x)) { HM_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define HM_ASSERT(x, ...)
	#define HM_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)