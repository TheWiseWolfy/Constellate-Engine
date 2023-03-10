#pragma once

#include "cslpch.h"

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



// Core log macros
#define CSL_CORE_LOG(...)    ::csl::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CSL_CORE_INFO(...)     ::csl::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CSL_CORE_WARN(...)     ::csl::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CSL_CORE_ERROR(...)    ::csl::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CSL_CORE_FATAL(...)    ::csl::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define CSL_TRACE(...)	       ::csl::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CSL_INFO(...)	       ::csl::Log::GetClientLogger()->info(__VA_ARGS__)
#define CSL_WARN(...)	       ::csl::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CSL_ERROR(...)	       ::csl::Log::GetClientLogger()->error(__VA_ARGS__)
#define CSL_FATAL(...)	       ::csl::Log::GetClientLogger()->fatal(__VA_ARGS__)
