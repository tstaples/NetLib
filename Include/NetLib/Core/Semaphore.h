#ifndef INCLUDED_NETLIB_SEMAPHORE
#define INCLUDED_NETLIB_SEMAPHORE
#pragma once


class Semaphore
{
public:
	enum State
	{
		Failed = -1,
		Signaled,
		Timeout
	};

public:
	Semaphore(u32 timeout);
	~Semaphore();

	State Wait();
	void Release();

private:
	void* mHandle;
	u32 mTimeout;
};

#endif