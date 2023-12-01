


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
	
	FOnInteractionGoalAchieved InteractionGoalActivationReqHandler;	
	InteractionGoalActivationReqHandler.BindDynamic(this, &UInteractableComponent::IOnInteractionGoalAchieved);
	IInteractableInterface::Execute_IBindToOnInteractionGoalAchieved(InteractionStrategyObject, InteractionGoalActivationReqHandler);

	FOnForceFinishInteraction ForceFinishInteractionActivationReqHandler;
	ForceFinishInteractionActivationReqHandler.BindDynamic(this, &UInteractableComponent::IOnForceFinishInteraction);
	IInteractableInterface::Execute_IBindToOnForceFinishInteraction(InteractionStrategyObject, ForceFinishInteractionActivationReqHandler);
}


void UInteractableComponent::IStartInteraction_Implementation(AActor *Interactor)
{
	if (!IsValid(InteractionStrategyClass)) return;
	OnInteractionStarted.Broadcast(Interactor, GetOwner());
	IInteractableInterface::Execute_IStartInteraction(InteractionStrategyObject, Interactor);
}

void UInteractableComponent::IBindToOnInteractionStarted_Implementation(const FOnInteractionStarted& Event)
{
	OnInteractionStarted.Add(Event);
}

void UInteractableComponent::IUnbindToOnInteractionStarted_Implementation(const FOnInteractionStarted& Event)
{
	OnInteractionStarted.Remove(Event);
}


void UInteractableComponent::IFinishInteraction_Implementation(AActor* Interactor)
{
	if (!IsValid(InteractionStrategyClass)) return;
	OnInteractionFinished.Broadcast(Interactor, GetOwner());
	IInteractableInterface::Execute_IFinishInteraction(InteractionStrategyObject, Interactor);
}

void UInteractableComponent::IBindToOnInteractionFinished_Implementation(const FOnInteractionFinished& Event)
{
	OnInteractionFinished.Add(Event);
}

void UInteractableComponent::IUnbindToOnInteractionFinished_Implementation(const FOnInteractionFinished& Event)
{
	OnInteractionFinished.Remove(Event);
}


void UInteractableComponent::IOnInteractionGoalAchieved_Implementation(AActor* Interactor, AActor* Interactable)
{
	OnInteractionGoalAchieved.Broadcast(Interactor, GetOwner());
}

void UInteractableComponent::IBindToOnInteractionGoalAchieved_Implementation(const FOnInteractionGoalAchieved& Event)
{
	OnInteractionGoalAchieved.Add(Event);
}

void UInteractableComponent::IUnbindToOnInteractionGoalAchieved_Implementation(const FOnInteractionGoalAchieved& Event)
{
	OnInteractionGoalAchieved.Remove(Event);
}


void UInteractableComponent::IOnForceFinishInteraction_Implementation(AActor* Interactor, AActor* Interactable)
{
	OnForceFinishInteraction.Broadcast(Interactor, GetOwner());
}

void UInteractableComponent::IBindToOnForceFinishInteraction_Implementation(const FOnForceFinishInteraction& Event)
{
	OnForceFinishInteraction.Add(Event);
}

