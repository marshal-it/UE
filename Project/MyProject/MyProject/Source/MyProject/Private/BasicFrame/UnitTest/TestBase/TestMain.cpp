#include "MyProject.h"
#include "TestMain.h"
#include "TestExtern.h"
#include "TestSocket.h"
#include "TestUI.h"

//#include "gtest/gtest.h"
#include "GrobalEvent.h"
#include "TestDownload.h"
#include "TestLuaBind.h"

#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"
#include "MyMemoryAlloc.h"

#include "Windows/AllowWindowsPlatformTypes.h"
#include <shellapi.h>
#include "Windows/HideWindowsPlatformTypes.h"

#include "SafePointer.h"

MY_BEGIN_NAMESPACE(MyNS)

TestMain::TestMain()
{
	this->mTestExtern = MY_NEW TestExtern();

#ifdef USE_EXTERN_THREAD

	this->mTestSocket = MY_NEW TestSocket();

#endif	// USE_EXTERN_THREAD

	this->mTestUI = MY_NEW TestUi();
	this->mTestDownload = MY_NEW TestDownload();
	this->mTestLuaBind = MY_NEW TestLuaBind();
}

TestMain::~TestMain()
{

}

void TestMain::init()
{

}

void TestMain::dispose()
{
	MY_SAFE_DISPOSE(this->mTestExtern);
	MY_SAFE_DISPOSE(this->mTestUI);
	MY_SAFE_DISPOSE(this->mTestDownload);
	MY_SAFE_DISPOSE(this->mTestLuaBind);
}

void TestMain::runTest()
{
	//const TCHAR* CmdLine = GetCommandLine();
	//LPWSTR *szArgList;
	//int argCount;
	//szArgList = CommandLineToArgvW(CmdLine, &argCount);

	//testing::AddGlobalTestEnvironment(new GrobalEvent);
	//testing::InitGoogleTest(&argCount, szArgList);

	////testing::InitGoogleTest(__argc, __argv);
	//RUN_ALL_TESTS();

	//this->mTestUI->run()
	//this->mTestDownload->run();
	this->mTestLuaBind->run();
}

MY_END_NAMESPACE