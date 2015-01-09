#ifndef INCLUDED_NETLIB_MUTEX
#define INCLUDED_NETLIB_MUTEX
#pragma once

#include <Windows.h>

class Mutex
{
public:
	Mutex(u32 timeout);
	~Mutex();

	void Lock();
	void Unlock();

private:
	CRITICAL_SECTION mMutexHandle;
	u32 mTimeout;
};

#endif