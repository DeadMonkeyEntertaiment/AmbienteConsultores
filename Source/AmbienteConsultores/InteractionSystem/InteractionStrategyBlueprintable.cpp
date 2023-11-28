#include "InteractionStrategyBlueprintable.h"


void UInteractionStrategyBlueprintable::IStartInteraction_Implementation(AActor* interactor)
{
	Interactor = interactor;

}

void UInteractionStrategyBlueprintable::InitializeObject_Implementation(AActor* owner)
{
	Owner = owner;
}

void UInteractionStrategyBlueprintable::Tick(float DeltaTime)
{	
	ObjectTick(DeltaTime);
}



