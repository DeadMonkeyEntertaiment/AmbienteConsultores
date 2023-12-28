#include "ProtectionGearComponent.h"

#include "ProtectionStrategy.h"


UProtectionGearComponent::UProtectionGearComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}

void UProtectionGearComponent::PutOn_Implementation()
{
	ProtectionStrategy->PutOn();
}

