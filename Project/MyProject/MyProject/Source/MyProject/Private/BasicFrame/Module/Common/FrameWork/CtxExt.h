#pragma once

#include "Ctx.h"
#include "MySharedPointer.h"

MY_BEGIN_NAMESPACE(MyNS)

class PlayerData;
class EntityData;
class ModuleSys;
class DataDelegate;
class DataEventCmd;

class CtxExt : public Ctx
{
protected:
	MySharedPtr<PlayerData> mPlayerData;
	MySharedPtr<EntityData> mEntityData;
	MySharedPtr<ModuleSys> mModuleSys;
	MySharedPtr<DataDelegate> mDataDelegate;
	MySharedPtr<DataEventCmd> mDataEventCmd;

public:
	CtxExt();

	virtual void construct() override;
	virtual void init() override;
	virtual void dispose() override;

	void setPlayerData(PlayerData* gameData);
	MySharedPtr<PlayerData> getPlayerData();

	void setEntityData(EntityData* entityData);
	MySharedPtr<EntityData> getEntityData();

	void setModuleSys(ModuleSys* moduleSys);
	MySharedPtr<ModuleSys> getModuleSys();

	MySharedPtr<DataDelegate> getDataDelegate();
	MySharedPtr<DataEventCmd> getDataEventCmd();
};

#define GCtxExt ((CtxExt*)(CtxExt::getSingletonPtr()))
#define GPlayerData GCtxExt->getPlayerData()
#define GEntityData GCtxExt->getEntityData()
#define GPlayerMgr GEntityData->getPlayerMgr()
#define GModuleSys GCtxExt->getModuleSys()
#define GDataDelegate GCtx->getDataDelegate()
#define GDataEventCmd GCtx->getDataEventCmd()

MY_END_NAMESPACE