﻿#pragma once

#include "PlayerChild.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class PlayerOtherChild : public PlayerChild
{
public:
	PlayerOtherChild()
	{
		this.mTypeId = "PlayerOtherChild";
		this.mEntityType = EntityType.ePlayerOtherChild;
		this.mMovement = new PlayerOtherChildMovement(this);
		this.mAttack = new PlayerOtherChildAttack(this);
		this.mEntityUniqueId = Ctx.msInstance.mPlayerMgr.genChildNewStrId();
	}

	virtual void initRender() override
	{
		if (!this.isPrefabPathValid())
		{
			this.setPrefabPath("World/Model/PlayerOther.prefab");
		}

		if (null == this.mRender)
		{
			this.mRender = new PlayerOtherChildRender(this);
		}

		this.mRender.init();
	}
};

MY_END_NAMESPACE