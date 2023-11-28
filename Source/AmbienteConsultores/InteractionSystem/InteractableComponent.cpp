


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
	InteractionStrategyObject->InitializeObject(GetOwner());
	FOnInteractionGoalAchieved ActivationReqHandler;
	ActivationReqHandler.BindDynamic(this, &UInteractableComponent::OnInteractionGoalAchieved);
	IInteractionStrategy::Execute_IBindToOnInteractionGoalAchieved(InteractionStrategyObject, ActivationReqHandler);	
}

void UInteractableComponent::EndInteraction_Implementation(AActor *Interactor)
{
	if (!IsValid(InteractionStrategyClass)) return;
	IInteractionStrategy::Execute_IEndInteraction(InteractionStrategyObject, Interactor);
}

void UInteractableComponent::StartInteraction_Implementation(AActor *Interactor)
{
	if (!IsValid(InteractionStrategyClass)) return;
	IInteractionStrategy::Execute_IStartInteraction(InteractionStrategyObject, Interactor);
}




