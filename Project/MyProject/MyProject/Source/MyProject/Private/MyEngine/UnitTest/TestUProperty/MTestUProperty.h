#pragma once

#include "GameFramework/Actor.h"
#include "MTestUProperty.generated.h"

//class UWindPointSourceComponent;
class UDrawSphereComponent;

/**
 * @brief Creating component subobjects and attaching them to the actor's hierarchy can also be done inside of the constructor. When spawning an actor, its components will be cloned from the CDO. In order to ensure that components are always created, destroyed, and properly garbage-collected, a pointer to every component created in the constructor should be stored in a UPROPERTY of the owning class. 
 * @ref https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/Reference/Classes/index.html
 */

UCLASS()
class AMTestUProperty : public AActor
{
    GENERATED_BODY()

public:
	AMTestUProperty();

    //UPROPERTY()
    //UWindPointSourceComponent* WindPointSource;

    UPROPERTY()
    UDrawSphereComponent* DisplaySphere;
};
