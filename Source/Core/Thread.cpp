#include "stdafx.h"
#include "Core/Thread.h"

#include <process.h>

// TODO: Move to separate file
struct BaseThreadFunctor
{
	virtual ~BaseThreadFunctor() {}
	virtual void Run() = 0;
};

// TODO: Variadic template to support n args
template<typename T>
struct ThreadFunctor : public BaseThreadFunctor
{
	ThreadFunctor(T functor) : mFunctor(functor) {}
	virtual void Run() { mFunctor(); }
	T mFunctor;
};

//----------------------------------------------------------------------------------------------------

Thread::~Thread()
{
	if (mEntryPoint)
	{
		SafeDelete(mEntryPoint);
	}
}
//----------------------------------------------------------------------------------------------------

bool Thread::Launch()
{
	mHandle = reinterpret_cast<HANDLE>(
		_beginthreadex(
			nullptr,				// Security
			65535,					// Stack size
			&entryPoint,			// Worker delegate
			this,					// Owner
			0,						// Run State
			&mThreadId));			// Thread Id

	if (mHandle)
	{
		mInitialized = true;
	}
	return mInitialized;
}
//----------------------------------------------------------------------------------------------------

bool Thread::Terminate()
{
	if (mInitialized)
	{
		// Wait for thread to exit gracefully
		ASSERT(mThreadId != GetCurrentThreadId(), "Thread cannot wait for self!");
		WaitForSingleObject(mHandle, mWaitTimeout);

		// Kill thread and cleanup
		CloseHandle(mHandle);
		mHandle = nullptr;
		mInitialized = false;
	}
	return mInitialized;
}
//----------------------------------------------------------------------------------------------------

void Thread::Run()
{
	// Call the user-defined functor
	ASSERT(mEntryPoint != nullptr, "Worker functor unitialized");
	mEntryPoint->Run();
}
//----------------------------------------------------------------------------------------------------

unsigned int __stdcall entryPoint(void* userData)
{
	Thread* owner = static_cast<Thread*>(userData);
	if (owner)
	{
		owner->Run();
	}

    // Optional, but it is cleaner
    _endthreadex(0);

    return 0;
}