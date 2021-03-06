﻿#pragma once

#include "GObject.h"
#include "IDispatchObject.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "TickMode.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class SceneEntityBase;

/**
 * @brief 移动类型
 */
class SceneEntityMovement : public GObject/*, public IDispatchObject*/
{
	M_DECLARE_CLASS(SceneEntityMovement, GObject)

protected:
	SceneEntityBase* mEntity;          // 关联的实体

public:
	SceneEntityMovement(SceneEntityBase* entity);

	virtual void init();
	virtual void dispose();
	virtual void onTick(float delta, TickMode tickMode);
};

MY_END_NAMESPACE