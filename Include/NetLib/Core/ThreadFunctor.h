#ifndef INCLUDED_NETLIB_THREADFUNCTOR
#define INCLUDED_NETLIB_THREADFUNCTOR
#pragma once

struct BaseThreadFunctor
{
	virtual ~BaseThreadFunctor() {}
	virtual void Run() = 0;
};

// TODO: Variadic template to support n args
template<typename T>
struct ThreadFunctor : public BaseThreadFunctor
{
	// User defined functor must have the '()' operator overloaded
	ThreadFunctor(T functor) : mFunctor(functor) {}
	virtual void Run() { mFunctor(); }
	T mFunctor;
};

#endif