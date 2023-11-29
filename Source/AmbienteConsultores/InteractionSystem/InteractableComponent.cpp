


#include "InteractableComponent.h"

#include "InteractionStrategy.h"


UInteractableComponent::UInteractableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractableComponent::BeginPlay()
{
	Super::BeginPlay();
	AActor * Owner = GetOwner();
	if (!IsValid(InteractionStrategyClass)) return;
	InteractionStrategyObject = NewObject<UInteractionStrategy>(Owner, InteractionStrategyClass);
	InteractionStrategyObject->InitializeObject(GetOwner());
	FOnInteractionGoalAchieved ActivationReqHandler;
	ActivationReqHandler.BindDynamic(this, &UInteractableComponent::IOnInteractionGoalAchieved);
	IInteractableInterface::Execute_IBindToOnInteractionGoalAchieved(InteractionStrategyObject, ActivationReqHandler);	
}

void UInteractableComponent::IEndInteraction_Implementation(AActor *Interactor)
{
	if (!IsValid(InteractionStrategyClass)) return;
	IInteractableInterface::Execute_IEndInteraction(InteractionStrategyObject, Interactor);
}

void UInteractableComponent::IStartInteraction_Implementation(AActor *Interactor)
{
	if (!IsValid(InteractionStrategyClass)) return;
	IInteractableInterface::Execute_IStartInteraction(InteractionStrategyObject, Interactor);
}




