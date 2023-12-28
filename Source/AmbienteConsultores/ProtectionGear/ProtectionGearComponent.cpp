#include "ProtectionGearComponent.h"

#include "ProtectionStrategy.h"


UProtectionGearComponent::UProtectionGearComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}

void UProtectionGearComponent::BeginPlay()
{
	Super::BeginPlay();
	
	AActor * Owner = GetOwner();
	
	//if (!IsValid(ProtectionStrategyClass)) return;
	
	//ProtectionStrategy = NewObject<UProtectionStrategy>(Owner, ProtectionStrategyClass);
}

void UProtectionGearComponent::PutOn_Implementation()
{
	ProtectionStrategy->PutOn(GetOwner());
}

