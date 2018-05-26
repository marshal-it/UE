﻿#include "MyProject.h"
#include "RefCountResLoadResultNotify.h"
#include "RefCount.h"

#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"
#include "MyMemoryAlloc.h"

RefCountResLoadResultNotify::RefCountResLoadResultNotify()
{
	this->mRefCount = MY_NEW RefCount();
}

RefCountResLoadResultNotify::~RefCountResLoadResultNotify()
{
	delete this->mRefCount;
}

RefCount* RefCountResLoadResultNotify::getRefCount()
{
	return this->mRefCount;
}

void RefCountResLoadResultNotify::setRefCount(RefCount* value)
{
	this->mRefCount = value;
}

void RefCountResLoadResultNotify::copyFrom(ResLoadResultNotify* rhv)
{
	ResLoadResultNotify::copyFrom(rhv);
	this->mRefCount->copyFrom(((RefCountResLoadResultNotify*)(rhv))->getRefCount());
}