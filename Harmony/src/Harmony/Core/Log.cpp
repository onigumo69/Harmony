#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Harmony
{

	Ref<spdlog::logger> Log::_core_logger;
	Ref<spdlog::logger> Log::_client_logger;

	void Log::init()
	{
		std::vector<spdlog::sink_ptr> logSinks;
		logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("Harmony.log", true));

		logSinks[0]->set_pattern("%^[%T] %n: %v%$");
		logSinks[1]->set_pattern("[%T] [%l] %n: %v");

		_core_logger = std::make_shared<spdlog::logger>("HARMONY", begin(logSinks), end(logSinks));
		spdlog::register_logger(_core_logger);
		_core_logger->set_level(spdlog::level::trace);
		_core_logger->flush_on(spdlog::level::trace);

		_client_logger = std::make_shared<spdlog::logger>("APP", begin(logSinks), end(logSinks));
		spdlog::register_logger(_client_logger);
		_client_logger->set_level(spdlog::level::trace);
		_client_logger->flush_on(spdlog::level::trace);
	}

}