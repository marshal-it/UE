﻿#include "MyProject.h"
#include "GameSceneInputNotify.h"
#include "Ctx.h"
#include "InputMgr.h"
#include "InputKey.h"
#include "InputEventId.h"
#include "EventDispatchDelegate.h"

MY_BEGIN_NAMESPACE(MyNS)

GameSceneInputNotify::GameSceneInputNotify()
{
            
}

void GameSceneInputNotify::init()
{
	GInputMgr->addKeyListener(
		InputKey::A,
		InputEventId::KEYUP_EVENT,
		MakeEventDispatchDelegate(
			this,
			&GameSceneInputNotify::onKeyUp,
			(uint)0
		)
	);
}

void GameSceneInputNotify::dispose()
{

}

void GameSceneInputNotify::onKeyDown(uint eventId, IDispatchObject* dispObj)
{
	InputKey* keyCode = (InputKey*)dispObj;
}

void GameSceneInputNotify::onKeyUp(uint eventId, IDispatchObject* dispObj)
{
	InputKey* keyCode = (InputKey*)dispObj;
}

void GameSceneInputNotify::onMouseDown()
{
            
}

void GameSceneInputNotify::onMouseUp()
{
            
}

MY_END_NAMESPACE