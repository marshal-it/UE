#pragma once

//#include "PhysicsEngine/DestructibleActor.h"
// Engine\Plugins\Runtime\ApexDestruction\Config\BaseApexDestruction.ini
// #include "ApexDestruction/DestructibleActor.h"
// D:\File\Self\UE\UE\Project\MyProject\MyProject\Source\MyProject\MyProject.Build.cs, ../../../../../ApexDestruction/Public
#include "DestructibleActor.h"

//PhysX 
#include "PhysXIncludes.h"
#include "PhysicsPublic.h"  //FPhysScene
#include "PhysXPublic.h"    //PtoU conversions
//For Scene Locking using Epic's awesome helper macros like SCOPED_SCENE_READ_LOCK
#include "Runtime/Engine/Private/PhysicsEngine/PhysXSupport.h"

#include "MyDestructibleActor.generated.h"

UCLASS(config = Game)
class AMyDestructibleActor : public ADestructibleActor
{
	GENERATED_BODY()

protected:
	virtual void Tick(float DeltaTime) override;

public:
	AMyDestructibleActor(const FObjectInitializer& ObjectInitializer);

	// https://wiki.unrealengine.com/PhysX,_Integrating_PhysX_Code_into_Your_Project
	FORCEINLINE void DrawPoint
		(
			const FVector& Loc,
			const float& Size = 7,
			const FColor& Color = FColor::Red,
			const float Duration = -1.f
			) const {
		DrawDebugPoint(
			GetWorld(),
			Loc,
			Size, //thickness
			Color,
			false,
			Duration
			);
	}

	FORCEINLINE void ScreenMsg(const FString& Msg)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *Msg);
	}

	FORCEINLINE void ScreenMsg(const FString& Msg, const FString& Msg2)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%s %s"), *Msg, *Msg2));
	}
};