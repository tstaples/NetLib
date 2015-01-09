#include "stdafx.h"
#include "Core/Mutex.h"

Mutex::Mutex(u32 timeout)
: mTimeout(timeout)
{
	InitializeCriticalSection(&mMutexHandle);
}

Mutex::~Mutex()
{
	DeleteCriticalSection(&mMutexHandle);
}

void Mutex::Lock()
{
	EnterCriticalSection(&mMutexHandle);
}

void Mutex::Unlock()
{
	LeaveCriticalSection(&mMutexHandle);
}