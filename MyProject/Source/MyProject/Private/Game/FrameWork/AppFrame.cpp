#include "MyProject.h"
#include "AppFrame.h"
#include "Common.h"

void AppFrame::initApp()
{
	Ctx::getSingletonPtr()->init();
	//Ctx::getSingletonPtr()->setUIMgr(new UIManager());
	//Ctx::getSingletonPtr()->setEngineApi(new EngineApi());
	//Ctx::getSingletonPtr()->setNetMgr(new NetMgr(Ctx::getSingletonPtr()->getStdLog()));

	// test
	//Ctx::getSingletonPtr()->getUIMgr()->loadForm(eUIPack);
	Ctx::getSingletonPtr()->getNetMgr()->openSocket("192.168.125.17", 10002);
}
