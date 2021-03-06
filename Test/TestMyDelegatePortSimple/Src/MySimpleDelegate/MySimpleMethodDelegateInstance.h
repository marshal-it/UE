#ifndef __MyMiniMethodDelegateInstance_H
#define __MyMiniMethodDelegateInstance_H

#include "MySimpleDelegateInstanceBase.h"

namespace MyNS
{

template <typename T>
class MySimpleMethodDelegateInstance;

template <typename T, typename R, typename... ParamTypes>
class MySimpleMethodDelegateInstance<R (T::*)(ParamTypes...)> : public MySimpleDelegateInstanceBase<R, ParamTypes...>
{
public:
    typedef R (T::*MethodPtrType)(ParamTypes...);

public:
	MySimpleMethodDelegateInstance(MethodPtrType func, T* callee)
        : mUserObject(callee)
        , mMethodPtr(func)
    {
	
	}

	virtual bool empty() const override
	{
		return (!this->mUserObject || !this->mMethodPtr);
	}

	virtual void clear() override
	{
		this->mUserObject = nullptr;
		this->mMethodPtr = nullptr;
	}

    R operator()(ParamTypes... args) const
    {
        return (this->mUserObject->*this->mMethodPtr)(args...);
    }

	virtual bool operator==(const MySimpleDelegateInstanceBase& other) const override
    {
		const MySimpleMethodDelegateInstance& rhv = (MySimpleMethodDelegateInstance&)other;

        return ((&this->mUserObject == &rhv.mUserObject) && 
			    (this->mMethodPtr == rhv.mMethodPtr));
    }

	virtual bool operator!= (const MySimpleDelegateInstanceBase& other) const override
    {
        return !((*this) == other);
    }

	virtual RetValType call(ParamTypes... Params) const override
	{
		return this->operator()(Params...);
	}

private:
    T* mUserObject;
    MethodPtrType mMethodPtr;
};

template <typename T, typename R, typename... ParamTypes>
class MySimpleMethodDelegateInstance<R (T::*)(ParamTypes...) const> : public MySimpleDelegateInstanceBase<R, ParamTypes...>
{
public:
    typedef R (T::*MethodPtrType)(ParamTypes...) const;

public:
	MySimpleMethodDelegateInstance(MethodPtrType func, const T* callee)
        : mUserObject(callee)
        , mMethodPtr(func)
    {
	
	}

	virtual bool empty() const override
	{
		return (!this->mUserObject || !this->mMethodPtr);
	}

	virtual void clear() override
	{
		this->mUserObject = nullptr;
		this->mMethodPtr = nullptr;
	}

    R operator()(ParamTypes... args) const
    {
        return (this->mUserObject->*mMethodPtr)(args...);
    }

	virtual bool operator==(const MySimpleDelegateInstanceBase& other) const override
    {
		const MySimpleMethodDelegateInstance& rhv = (MySimpleMethodDelegateInstance&)other;

        return ((&this->mUserObject == &rhv.mUserObject) && 
			    (this->mMethodPtr == rhv.mMethodPtr));
    }

	virtual bool operator!= (const MySimpleDelegateInstanceBase& other) const override
    {
        return !(*this == other);
    }

	virtual RetValType call(ParamTypes... Params) const override
	{
		return this->operator()(Params...);
	}

private:
    const T* mUserObject;
    MethodPtrType mMethodPtr;
};

/**
 * @brief 非成员函数没有 const 偏特化
 */
template <typename R, typename... ParamTypes>
class MySimpleMethodDelegateInstance<R (*)(ParamTypes...)> : public MySimpleDelegateInstanceBase<R, ParamTypes...>
{
public:
    typedef R (*MethodPtrType)(ParamTypes...);

public:
	MySimpleMethodDelegateInstance(MethodPtrType func)
        : mMethodPtr(func)
    {
	
	}

	virtual bool empty() const override
	{
		return !this->mMethodPtr;
	}

	virtual void clear() override
	{
		this->mMethodPtr = nullptr;
	}

    R operator()(ParamTypes... args) const
    {
        return (*this->mMethodPtr)(args...);
    }

	virtual bool operator==(const MySimpleDelegateInstanceBase& other) const override
    {
		const MySimpleMethodDelegateInstance& rhv = (MySimpleMethodDelegateInstance&)other;

        return this->mMethodPtr == rhv.mMethodPtr;
    }

	virtual bool operator!= (const MySimpleDelegateInstanceBase& other) const override
    {
        return !((*this) == other);
    }

	virtual RetValType call(ParamTypes... Params) const override
	{
		return this->operator()(Params...);
	}

private:
    MethodPtrType mMethodPtr;
};

template <typename F, typename T>
MySimpleMethodDelegateInstance<F>* makeDelegate(F func, T* obj)
{
    return new MySimpleMethodDelegateInstance<F>(func, obj);
}

template <typename T>
MySimpleMethodDelegateInstance<T>* makeDelegate(T func)
{
    return new MySimpleMethodDelegateInstance<T>(func);
}

}

#endif