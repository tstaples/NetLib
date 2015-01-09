#ifndef INCLUDED_NETLIB_COMMON
#define INCLUDED_NETLIB_COMMON
#pragma once

#include <string>
#include <vector>
#include <map>

//====================================================================================================
// Typedefs
//====================================================================================================

typedef char				s8;
typedef short				s16;
typedef int					s32;
typedef __int64				s64;

typedef unsigned char		u8;
typedef unsigned short		u16;
typedef unsigned int		u32;
typedef unsigned __int64	u64;

typedef float				f32;
typedef double				f64;

//====================================================================================================
// Macros
//====================================================================================================

#if defined(_DEBUG)
	#define LOG(format, ...)\
	{\
		{\
			va_list va;\
			char buffer[1024];\
			va_start(va, (#format));\
			vsprintf_s(buffer, 1024, (#format), va);\
			va_end(va);\
			std::string message;\
			message += (buffer);\
			message += "\n";\
			OutputDebugStringA(message.c_str());\
		}\
	}
#else
	#define LOG(format, ...)
#endif

//----------------------------------------------------------------------------------------------------

#if defined(_DEBUG)
	#define ASSERT(condition, format, ...)\
	{\
		if (!(condition))\
		{\
			LOG(format, ...)\
			DebugBreak();\
		}\
	}
#else
	#define ASSERT(condition, format, ...)
#endif

//----------------------------------------------------------------------------------------------------

// Requires C++11
#define NONCOPYABLE(type)\
	type(const type&) = delete;\
	type& operator=(const type&) = delete;

//====================================================================================================
// Helper Functions
//====================================================================================================

template <typename T>
inline void SafeDelete(T*& ptr)
{
	delete ptr;
	ptr = nullptr;
}

//----------------------------------------------------------------------------------------------------

template <typename T>
inline void SafeDeleteArray(T*& ptr)
{
	delete[] ptr;
	ptr = nullptr;
}

#endif