#pragma once

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <thread>

namespace Harmony
{

	struct ProfileResult
	{
		std::string _name;
		long long _start, _end;
		uint32_t _thread_id;
	};

	struct InstrumentationSession
	{
		std::string _name;
	};

	class Instrumentor
	{
	private:
		InstrumentationSession* _current_session;
		std::ofstream _output_stream;
		int _profile_count;
	public:
		Instrumentor()
			: _current_session(nullptr), _profile_count(0)
		{}

		void begin_session(const std::string& name, const std::string& filepath = "results.json")
		{
			_output_stream.open(filepath);
			write_header();
			_current_session = new InstrumentationSession{ name };
		}

		void end_session()
		{
			write_footer();
			_output_stream.close();
			delete _current_session;
			_current_session = nullptr;
			_profile_count = 0;
		}

		void write_profile(const ProfileResult& result)
		{
			if (_profile_count++ > 0)
				_output_stream << ",";

			std::string name = result._name;
			std::replace(name.begin(), name.end(), '"', '\'');

			_output_stream << "{";
			_output_stream << "\"cat\":\"function\",";
			_output_stream << "\"dur\":" << (result._end - result._start) << ',';
			_output_stream << "\"name\":\"" << name << "\",";
			_output_stream << "\"ph\":\"X\",";
			_output_stream << "\"pid\":0,";
			_output_stream << "\"tid\":" << result._thread_id << ",";
			_output_stream << "\"ts\":" << result._start;
			_output_stream << "}";

			_output_stream.flush();
		}

		void write_header()
		{
			_output_stream << "{\"otherData\": {},\"traceEvents\":[";
			_output_stream.flush();
		}

		void write_footer()
		{
			_output_stream << "]}";
			_output_stream.flush();
		}

		static Instrumentor& get()
		{
			static Instrumentor instance;
			return instance;
		}
	};

	class InstrumentationTimer
	{
	public:
		InstrumentationTimer(const char* name)
			: _name(name), _stopped(false)
		{
			_start_time_point = std::chrono::high_resolution_clock::now();
		}

		~InstrumentationTimer()
		{
			if (!_stopped)
				stop();
		}

		void stop()
		{
			auto endTimepoint = std::chrono::high_resolution_clock::now();

			long long start = std::chrono::time_point_cast<std::chrono::microseconds>(_start_time_point).time_since_epoch().count();
			long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

			uint32_t thread_id = std::hash<std::thread::id>{}(std::this_thread::get_id());
			Instrumentor::get().write_profile({ _name, start, end, thread_id });

			_stopped = true;
		}
	private:
		const char* _name;
		std::chrono::time_point<std::chrono::high_resolution_clock> _start_time_point;
		bool _stopped;
	};
}

#define HM_PROFILE 1
#if HM_PROFILE
#define HM_PROFILE_BEGIN_SESSION(name, filepath) ::Harmony::Instrumentor::get().begin_session(name, filepath)
#define HM_PROFILE_END_SESSION() ::Harmony::Instrumentor::get().end_session()
#define HM_PROFILE_SCOPE(name) ::Harmony::InstrumentationTimer timer##__LINE__(name);
#define HM_PROFILE_FUNCTION() HM_PROFILE_SCOPE(__FUNCSIG__)
#else
#define HM_PROFILE_BEGIN_SESSION(name, filepath)
#define HM_PROFILE_END_SESSION()
#define HM_PROFILE_SCOPE(name)
#define HM_PROFILE_FUNCTION()
#endif