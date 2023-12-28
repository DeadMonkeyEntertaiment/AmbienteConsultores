
#include "BaseProtectionGear.h"

#include "ProtectionGearComponent.h"


ABaseProtectionGear::ABaseProtectionGear()
{	
	PrimaryActorTick.bCanEverTick = false;
	ProtectionGearComponent = CreateDefaultSubobject<UProtectionGearComponent>(TEXT("ProtectionGearComponent"));
}


