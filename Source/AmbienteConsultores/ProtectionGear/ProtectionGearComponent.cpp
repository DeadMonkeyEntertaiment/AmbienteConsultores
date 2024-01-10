#include "ProtectionGearComponent.h"

#include "ProtectionStrategy.h"


UProtectionGearComponent::UProtectionGearComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UProtectionGearComponent::Setup(bool Necessary, int StackNum, FTransform Location)
{
	IsNecessary = Necessary;
	StackNumber = StackNum;
	SpawnedLocation = Location;
}

void UProtectionGearComponent::BindToOnPutOn(const FOnPutOnInternal& event)
{
	ProtectionStrategyObject->OnPutOn.AddUnique(event);
}

void UProtectionGearComponent::PutOn_Implementation(AActor* player)
{
	ProtectionStrategyObject->PutOn(player);
}

void UProtectionGearComponent::Remove_Implementation()
{
	OnEppRemoved.Broadcast(GetOwner());
	ProtectionStrategyObject->Remove();
}

