#include "stdafx.h"
#include "Core/Semaphore.h"
#include <Windows.h>

Semaphore::Semaphore(u32 timeout)
: mTimeout(timeout)
{
	mHandle = CreateSemaphore(nullptr, 0, 1000, NULL);
	ASSERT(mHandle != nullptr, "Semaphore failed to initialize");
}
//----------------------------------------------------------------------------------------------------

Semaphore::~Semaphore()
{
	CloseHandle(mHandle);
}
//----------------------------------------------------------------------------------------------------

Semaphore::State Semaphore::Wait()
{
	u32 rc = WaitForSingleObject(mHandle, mTimeout);
	switch (rc)
	{
	case WAIT_OBJECT_0:
		return Semaphore::Signaled;	// Object was retrieved
	case WAIT_TIMEOUT:
		return Semaphore::Timeout;	// Timeout expired while waiting
	}
	return Semaphore::Failed;		// Object not retrieved
}
//----------------------------------------------------------------------------------------------------

void Semaphore::Release()
{
	::ReleaseSemaphore(mHandle, 1, NULL);
}