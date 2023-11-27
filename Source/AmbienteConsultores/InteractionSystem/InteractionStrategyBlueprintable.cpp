#include "InteractionStrategyBlueprintable.h"


void UInteractionStrategyBlueprintable::IStartInteraction_Implementation(AActor* interactor, AActor* interactable)
{
	Interactor = interactor;
	Interactable = interactable;
}

void UInteractionStrategyBlueprintable::Tick(float DeltaTime)
{	
	ObjectTick(DeltaTime);
}



