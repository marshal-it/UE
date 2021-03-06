﻿#ifndef __SystemFrameData_H
#define __SystemFrameData_H

#include "Platform.h"
#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class SystemFrameData : public GObject
{
protected:
	uint32 mTotalFrameCount;       // 当前帧数
    uint32 mCurFrameCount;         // 当前帧数
    float mCurTime;          // 当前一秒内时间
    int mFps;                // 帧率

public:
	SystemFrameData();

public:
	void init();
	void dispose();

	uint32 getTotalFrameCount();
	void nextFrame(float delta);
};

MY_END_NAMESPACE

#endif