#include "InteractionStrategy.h"


void UInteractionStrategy::IStartInteraction_Implementation(AActor* interactor)
{
	Interactor = interactor;

}

void UInteractionStrategy::InitializeObject_Implementation(AActor* owner)
{
	Owner = owner;
}

void UInteractionStrategy::Tick(float DeltaTime)
{	
	ObjectTick(DeltaTime);
}



