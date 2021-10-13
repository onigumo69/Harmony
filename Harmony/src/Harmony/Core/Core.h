#pragma once

#include <memory>

#if HM_DYNAMIC_LINK
#ifdef HARMONY_BUILD_DLL
	#define HARMONY_API __declspec(dllexport)
#else
	#define HARMONY_API __declspec(dllimport)
#endif
#else
	#define HARMONY_API
#endif

#ifdef HM_DEBUG
	#define HM_ENABLE_ASSERTS
#endif

#ifdef HM_ENABLE_ASSERTS
	#define HM_ASSERT(x, ...) { if(!(x)) { HM_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define HM_CORE_ASSERT(x, ...) { if(!(x)) { HM_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define HM_ASSERT(x, ...)
	#define HM_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define HM_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Harmony
{

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> create_scope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> create_ref(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}