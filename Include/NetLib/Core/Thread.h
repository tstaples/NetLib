#ifndef INCLUDED_NETLIB_THREAD
#define INCLUDED_NETLIB_THREAD
#pragma once

#include <Windows.h>

struct BaseThreadFunctor;

class Thread
{
public:
	template<typename F>
	Thread(F function, u32 waitTime = INFINITE);
	~Thread();

	bool Launch();
	bool Terminate();
	void Run();

private:
	NONCOPYABLE(Thread);

	friend unsigned int __stdcall entryPoint(void* userData);
	BaseThreadFunctor* mEntryPoint;

	bool mInitialized;
	HANDLE mHandle;
	const u32 mWaitTimeout;
	u32 mThreadId;
};


template<typename F>
Thread::Thread(F function, u32 waitTime)
	: mEntryPoint(new ThreadFunctor<F>(function))
	, mWaitTimeout(waitTime)
	, mHandle(nullptr)
	, mInitialized(false)
	, mThreadId(0)
{
}

#endif