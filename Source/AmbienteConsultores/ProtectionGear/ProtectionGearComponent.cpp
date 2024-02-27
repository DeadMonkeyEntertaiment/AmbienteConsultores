#include "ProtectionGearComponent.h"

#include "ProtectionStrategy.h"


UProtectionGearComponent::UProtectionGearComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UProtectionGearComponent::Setup(bool Necessary, int StackNum, FTransform Transform)
{
	IsNecessary = Necessary;
	StackNumber = StackNum;
	SpawnedTransform = Transform;
}

void UProtectionGearComponent::BindToOnPutOn(const FOnPutOnInternal& event)
{
	if (!IsValid(ProtectionStrategyObject)) return;;
	ProtectionStrategyObject->OnPutOn.AddUnique(event);
}

void UProtectionGearComponent::Equip_Implementation(AActor* player)
{
	GetOwner()->SetActorHiddenInGame(true);
	GetOwner()->SetActorEnableCollision(false);
	if (!IsValid(ProtectionStrategyObject)) return;;
	ProtectionStrategyObject->Equip(player);
}

void UProtectionGearComponent::Remove_Implementation()
{
	OnEppRemoved.Broadcast(GetOwner());
	GetOwner()->SetActorTransform(SpawnedTransform);
	GetOwner()->SetActorHiddenInGame(false);
	GetOwner()->SetActorEnableCollision(true);
	if (!IsValid(ProtectionStrategyObject)) return;	
	ProtectionStrategyObject->Remove();	
}

