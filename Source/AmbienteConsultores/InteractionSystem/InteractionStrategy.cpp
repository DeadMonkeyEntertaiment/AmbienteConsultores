#include "InteractionStrategy.h"


void UInteractionStrategy::IStartInteraction_Implementation(AActor* interactor)
{
	Interactor = interactor;
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



