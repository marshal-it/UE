#ifndef __ENGINEAPI_H
#define __ENGINEAPI_H

class UGameInstance;
class UMyProjectEngine;
class UMyProjectGameInstance;

class EngineApi
{
public:
	virtual UGameInstance* getGameInstance();
	virtual UWorld* getWorld();
	virtual void showCursor();
	UMyProjectEngine* getEngine();
	UMyProjectGameInstance* getMyProjectGameInstanceByEngine();
	UWorld* getWorldByEngine();

	ACharacter* getFirstCharacter();	// 获取第一个 ACharacter ，就是主角自己

	static void addEventHandle(UButton* pBtn, UObject* pFuncObj, FName funcName);
};

#endif				// __ENGINEAPI_H