#pragma once

#include "Core/Log.h"

#ifdef CSL_ENABLE_ASSERTS
#define CSL_ASSERT(x, ...) { if(!(x)) { CSL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define CSL_CORE_ASSERT(x, ...) { if(!(x)) { CSL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define CSL_ASSERT(x, ...)
#define CSL_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)


class NotImplementedException : public std::logic_error
{
public:
	NotImplementedException() : std::logic_error("Function not yet implemented") { };
};