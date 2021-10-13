#pragma once

#include <memory>

#include "Core.h"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Harmony
{

	class Log
	{
	public:
		static void init();

		inline static Ref<spdlog::logger>& get_core_logger() { return _core_logger; }
		inline static Ref<spdlog::logger>& get_client_logger() { return _client_logger; }
	private:
		static Ref<spdlog::logger> _core_logger;
		static Ref<spdlog::logger> _client_logger;
	};

}

// Core log macros
#define HM_CORE_TRACE(...)    ::Harmony::Log::get_core_logger()->trace(__VA_ARGS__)
#define HM_CORE_INFO(...)     ::Harmony::Log::get_core_logger()->info(__VA_ARGS__)
#define HM_CORE_WARN(...)     ::Harmony::Log::get_core_logger()->warn(__VA_ARGS__)
#define HM_CORE_ERROR(...)    ::Harmony::Log::get_core_logger()->error(__VA_ARGS__)
#define HM_CORE_FATAL(...)    ::Harmony::Log::get_core_logger()->critical(__VA_ARGS__)
								
// Client log macros
#define HM_TRACE(...)	      ::Harmony::Log::get_client_logger()->trace(__VA_ARGS__)
#define HM_INFO(...)	      ::Harmony::Log::get_client_logger()->info(__VA_ARGS__)
#define HM_WARN(...)	      ::Harmony::Log::get_client_logger()->warn(__VA_ARGS__)
#define HM_ERROR(...)	      ::Harmony::Log::get_client_logger()->error(__VA_ARGS__)
#define HM_FATAL(...)	      ::Harmony::Log::get_client_logger()->critical(__VA_ARGS__)