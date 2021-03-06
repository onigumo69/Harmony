#pragma once

#include <memory>

#ifdef HM_DEBUG
	#define HM_ENABLE_ASSERTS
	#define HM_DEBUGBREAK() __debugbreak()
#else
	#define HM_DEBUGBREAK()
#endif

#ifdef HM_ENABLE_ASSERTS
	#define HM_ASSERT(x, ...) { if(!(x)) { HM_ERROR("Assertion Failed: {0}", __VA_ARGS__); HM_DEBUGBREAK(); } }
	#define HM_CORE_ASSERT(x, ...) { if(!(x)) { HM_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); HM_DEBUGBREAK(); } }
#else
	#define HM_ASSERT(x, ...)
	#define HM_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define HM_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

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