#include "InteractionStrategy.h"


void UInteractionStrategy::IStartInteraction_Implementation(AActor* interactor)
{
	Interactor = interactor;
	bInteracted = true;
}

void UInteractionStrategy::IFinishInteraction_Implementation(AActor* interactor)
{
	bInteracted = false;
}

bool UInteractionStrategy::IIsInteracted_Implementation()
{
	return bInteracted;
}

void UInteractionStrategy::IBindToOnInteractionGoalAchieved_Implementation(const FOnInteractionGoalAchieved& Event)
{
	OnInteractionGoalAchievedInternal.Add(Event);
}

void UInteractionStrategy::IBindToOnForceFinishInteraction_Implementation(const FOnForceFinishInteraction& Event)
{
	OnForceFinishInteractionInternal.Add(Event);
}

void UInteractionStrategy::InitializeObject_Implementation(AActor* owner)
{
	Owner = owner;
}

void UInteractionStrategy::Tick(float DeltaTime)
{	
	ObjectTick(DeltaTime);
}



