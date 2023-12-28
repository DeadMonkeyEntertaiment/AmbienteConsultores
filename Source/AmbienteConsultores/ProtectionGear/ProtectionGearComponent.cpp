#include "ProtectionGearComponent.h"

#include "ProtectionStrategy.h"


UProtectionGearComponent::UProtectionGearComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UProtectionGearComponent::PutOn_Implementation()
{
	ProtectionStrategyObject->PutOn(GetOwner());
}

void UProtectionGearComponent::Remove_Implementation()
{
	ProtectionStrategyObject->Remove();
}

