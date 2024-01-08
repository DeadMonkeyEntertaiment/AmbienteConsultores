


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
	
	if (!IsValid(InteractionStrategyObject)) return;	
	InteractionStrategyObject->InitializeObject(GetOwner());	
	
	FOnInteractionGoalAchieved InteractionGoalActivationReqHandler;	
	InteractionGoalActivationReqHandler.BindDynamic(this, &UInteractableComponent::IOnInteractionGoalAchieved);
	IInteractableInterface::Execute_IBindToOnInteractionGoalAchieved(InteractionStrategyObject, InteractionGoalActivationReqHandler);

	FOnForceFinishInteraction ForceFinishInteractionActivationReqHandler;
	ForceFinishInteractionActivationReqHandler.BindDynamic(this, &UInteractableComponent::IOnForceFinishInteraction);
	IInteractableInterface::Execute_IBindToOnForceFinishInteraction(InteractionStrategyObject, ForceFinishInteractionActivationReqHandler);
	OnStrategyInitialized.Broadcast(InteractionStrategyObject);
}


bool UInteractableComponent::IIsEnabled_Implementation()
{
	return bEnable;
}

void UInteractableComponent::ISetEnabled_Implementation(bool NewState)
{
	bEnable = NewState;
}

bool UInteractableComponent::IIsInteracted_Implementation()
{
	return bInteracted;
}

void UInteractableComponent::IStartInteraction_Implementation(AActor *Interactor)
{
	if (!IIsEnabled_Implementation()) return;
	if (!IsValid(InteractionStrategyObject)) return;
	bInteracted =true;
	NewInteractor = Interactor;
	OnInteractionStartedInternal.Broadcast(Interactor, GetOwner());
	IInteractableInterface::Execute_IStartInteraction(InteractionStrategyObject, Interactor);
}

void UInteractableComponent::IBindToOnInteractionStarted_Implementation(const FOnInteractionStarted& Event)
{
	OnInteractionStartedInternal.Add(Event);
}

void UInteractableComponent::IUnbindToOnInteractionStarted_Implementation(const FOnInteractionStarted& Event)
{
	OnInteractionStartedInternal.Remove(Event);	
}


void UInteractableComponent::IFinishInteraction_Implementation(AActor* Interactor)
{
	if (!IsValid(InteractionStrategyObject)) return;
	if (!IIsEnabled_Implementation()) return;
	bInteracted = false;
	OnInteractionFinishedInternal.Broadcast(Interactor, GetOwner());
	IInteractableInterface::Execute_IFinishInteraction(InteractionStrategyObject, Interactor);
}

void UInteractableComponent::IBindToOnInteractionFinished_Implementation(const FOnInteractionFinished& Event)
{
	OnInteractionFinishedInternal.Add(Event);
}

void UInteractableComponent::IUnbindToOnInteractionFinished_Implementation(const FOnInteractionFinished& Event)
{
	OnInteractionFinishedInternal.Remove(Event);
}


void UInteractableComponent::IOnInteractionGoalAchieved_Implementation(AActor* Interactor, AActor* Interactable)
{
	OnInteractionGoalAchievedInternal.Broadcast(Interactor, GetOwner());
}

void UInteractableComponent::IBindToOnInteractionGoalAchieved_Implementation(const FOnInteractionGoalAchieved& Event)
{
	OnInteractionGoalAchievedInternal.Add(Event);
}

void UInteractableComponent::IUnbindToOnInteractionGoalAchieved_Implementation(const FOnInteractionGoalAchieved& Event)
{
	OnInteractionGoalAchievedInternal.Remove(Event);
}


void UInteractableComponent::IOnForceFinishInteraction_Implementation(AActor* Interactor, AActor* Interactable)
{
	OnForceFinishInteractionInternal.Broadcast(Interactor, GetOwner());
}

void UInteractableComponent::IBindToOnForceFinishInteraction_Implementation(const FOnForceFinishInteraction& Event)
{
	OnForceFinishInteractionInternal.Add(Event);
}

