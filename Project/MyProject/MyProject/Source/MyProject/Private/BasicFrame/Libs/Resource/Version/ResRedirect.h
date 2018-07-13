﻿#pragma once

#include <string>
#include "MDictionary.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class ResRedirectItem;

/**
 * @brief 资源重定向，确定资源最终位置
 */
class ResRedirect
{
protected:
	MDictionary<std::string, ResRedirectItem*> mOrigPath2ItemDic;   // 原始的资源加载目录
    MDictionary<std::string, ResRedirectItem*> mABPath2ItemDic;     // AB 资源加载目录

public:
	ResRedirect();

	void init();
	void dispose();

    // 清理之前缓存信息
	void clearCacheInfo();
    // 资源是否可以重定向，只有在 Version_S.txt 或者在 Version_P.txt 中的资源才能判断是存在的
	bool canResRedirect(std::string origPath, bool isABAsset);
    // isABAsset 是否是 AssetBundles 资源目录
	ResRedirectItem* getResRedirectItem(std::string origPath, bool isABAsset);
};

MY_END_NAMESPACE