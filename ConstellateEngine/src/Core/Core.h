#pragma once

#ifdef CSL_PLATFORM_WINDOWS
	#define HAZEL_API __declspec(dllexport)
#else
	#error Hazel only supports Windows!
#endif