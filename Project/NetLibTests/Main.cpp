#include <iostream>

#include <NetLib/NetLib.h>

static int someCount = 0;

struct MyFunctor
{
	int mThreadNum;
	Mutex* mutex;
	MyFunctor(int threadNum, Mutex& mtx)
		: mThreadNum(threadNum)
		, mutex(&mtx)
	{
	}

	void operator()()
	{
		for (int i=0; i < 100; ++i)
		{
			mutex->Lock();
			std::cout << "[Thread " << mThreadNum << "] Count is at: " << (someCount++) << std::endl;
			mutex->Unlock();
		}
	}
};

int main()
{
	Mutex mutex(1000);
	Thread threadA(MyFunctor(1, mutex));
	Thread threadB(MyFunctor(2, mutex));
	
	ASSERT(threadA.Launch(), "Thread A failed to launch");
	ASSERT(threadB.Launch(), "Thread A failed to launch");
	
	threadA.Terminate();
	threadB.Terminate();

	return 0;
}