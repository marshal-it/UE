﻿#pragma once

#include "AuxLoaderBase.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "ResPackType.h"
#include <string>		// std::string
#include "EventDispatchDelegate.h"		// EventDispatchDelegate
#include "PlatformDefine.h"

class UTexture;

MY_BEGIN_NAMESPACE(MyNS)

class IDispatchObject;
class TextureInsRes;

class AuxTextureLoader : public AuxLoaderBase
{
	M_DECLARE_CLASS(AuxTextureLoader, AuxLoaderBase)

protected :
	TextureInsRes* mTextureRes;		// 纹理资源
	UTexture* mTexture;		// 纹理是 Asset-Object 资源，因此卸载这些资源都在 Ins 管理器处理

public:
	AuxTextureLoader();

	virtual void dispose() override;
	UTexture* getTexture();
	virtual std::string getOrigPath() override;

	virtual void syncLoad(
		std::string path,
		EventDispatchDelegate evtHandle = nullptr,
		EventDispatchDelegate progressHandle = nullptr
	) override;
    // 异步加载对象
	virtual void asyncLoad(
		std::string path,
		EventDispatchDelegate evtHandle,
		EventDispatchDelegate progressHandle = nullptr
	) override;
	void onTextureLoaded(IDispatchObject* dispObj);
	virtual void unload() override;
};

MY_END_NAMESPACE