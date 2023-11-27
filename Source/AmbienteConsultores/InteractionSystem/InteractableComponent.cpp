


#include "InteractableComponent.h"

#include "InteractionStrategyBlueprintable.h"


UInteractableComponent::UInteractableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractableComponent::BeginPlay()
{
	Super::BeginPlay();
	AActor * Owner = GetOwner();
	if (!IsValid(InteractionStrategyClass)) return;
	InteractionStrategyObject = NewObject<UInteractionStrategyBlueprintable>(Owner, InteractionStrategyClass);
}

void UInteractableComponent::EndInteraction_Implementation(AActor *Interactor)
{
	if (!IsValid(InteractionStrategyClass)) return;
	IInteractionStrategy::Execute_IEndInteraction(InteractionStrategyObject, Interactor, GetOwner());
}

void UInteractableComponent::StartInteraction_Implementation(AActor *Interactor)
{
	if (!IsValid(InteractionStrategyClass)) return;
	IInteractionStrategy::Execute_IStartInteraction(InteractionStrategyObject, Interactor, GetOwner());
}




