#include "MyProject.h"
#include "MyFlyGameViewportClient.h"

UMyFlyGameViewportClient::UMyFlyGameViewportClient(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

TOptional<bool> UMyFlyGameViewportClient::QueryShowFocus(const EFocusCause InFocusCause) const
{
	// Consider your own special logic, you might want to call the super method first.
	return false;
}