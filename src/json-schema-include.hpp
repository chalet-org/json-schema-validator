#pragma once

#if (defined(__cpp_exceptions) || defined(__EXCEPTIONS) || defined(_CPPUNWIND))
	#ifndef JSONSV_EXCEPTIONS
		#define JSONSV_EXCEPTIONS
	#endif

	#define JSONSV_THROW(exception) throw exception
	#define JSONSV_TRY try
	#define JSONSV_CATCH(exception) catch (exception)
	#define JSONSV_EXCEPT_ERROR(...) Diagnostic::error(__VA_ARGS__);
#else
	#include <cstdlib>
	#define JSONSV_THROW(exception) std::abort()
	#define JSONSV_TRY if (true)
	#define JSONSV_CATCH(exception) if (false)
	#define JSONSV_EXCEPT_ERROR(...)
#endif

#if !defined(JSONSV_EXCEPTIONS)
	#define JSON_NOEXCEPTION
#endif

#ifdef _MSC_VER
	// #pragma warning(push)
	// #pragma warning(disable : 4100)
#else
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wpedantic"
	#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

#include <nlohmann/json.hpp>

#ifdef _MSC_VER
	// #pragma warning(pop)
#else
	#pragma GCC diagnostic pop
#endif
