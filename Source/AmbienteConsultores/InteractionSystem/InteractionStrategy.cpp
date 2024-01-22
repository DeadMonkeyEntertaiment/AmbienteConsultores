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
	OnInteractionGoalAchievedInternal.AddUnique(Event);
}

void UInteractionStrategy::IBindToOnForceFinishInteraction_Implementation(const FOnForceFinishInteraction& Event)
{
	OnForceFinishInteractionInternal.AddUnique(Event);
}

void UInteractionStrategy::InitializeObject_Implementation(AActor* owner)
{	
	Owner = owner;
	if (!IsValid(Owner)) return;

	SpawnLocation = Owner->GetActorLocation();
	SpawnRotation = Owner->GetActorRotation();
	if (!IsValid(Owner->GetComponentByClass<UStaticMeshComponent>())) return;
	Owner->GetComponentByClass<UStaticMeshComponent>()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}