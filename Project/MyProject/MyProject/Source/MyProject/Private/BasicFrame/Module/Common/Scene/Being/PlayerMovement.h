﻿#pragma once

#include "SceneEntityBase.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

public class PlayerMovement : BeingEntityMovement
{
	public PlayerMovement(SceneEntityBase entity)
		: base(entity)
	{

	}
};

MY_END_NAMESPACE