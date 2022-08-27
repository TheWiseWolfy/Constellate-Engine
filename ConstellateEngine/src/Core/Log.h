#pragma once

//#include <memory>
#include <memory>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

//Class that takes care of logging across all the engine systems


namespace csl{

	class Log {
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	public:
		static void Init();

		 static std::shared_ptr<spdlog::logger>& GetCoreLogger();
		 static std::shared_ptr<spdlog::logger>& GetClientLogger();
	};
}