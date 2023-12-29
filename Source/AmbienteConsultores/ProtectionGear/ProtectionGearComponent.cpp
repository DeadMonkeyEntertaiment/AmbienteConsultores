#include "ProtectionGearComponent.h"

#include "ProtectionStrategy.h"


UProtectionGearComponent::UProtectionGearComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UProtectionGearComponent::PutOn_Implementation(AActor* player)
{
	ProtectionStrategyObject->PutOn(player);
}

void UProtectionGearComponent::Remove_Implementation()
{
	ProtectionStrategyObject->Remove();
}

