


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
	
	if (!IsValid(InteractionStrategy)) return;	
	InteractionStrategy->InitializeObject(GetOwner());	
	
	FOnInteractionGoalAchieved InteractionGoalActivationReqHandler;	
	InteractionGoalActivationReqHandler.BindDynamic(this, &UInteractableComponent::IOnInteractionGoalAchieved);
	IInteractableInterface::Execute_IBindToOnInteractionGoalAchieved(InteractionStrategy, InteractionGoalActivationReqHandler);

	FOnForceFinishInteraction ForceFinishInteractionActivationReqHandler;
	ForceFinishInteractionActivationReqHandler.BindDynamic(this, &UInteractableComponent::IOnForceFinishInteraction);
	IInteractableInterface::Execute_IBindToOnForceFinishInteraction(InteractionStrategy, ForceFinishInteractionActivationReqHandler);
	OnStrategyInitialized.Broadcast(InteractionStrategy);
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
	if (!IsValid(InteractionStrategy)) return;
	bInteracted =true;
	NewInteractor = Interactor;
	OnInteractionStartedInternal.Broadcast(Interactor, GetOwner());
	IInteractableInterface::Execute_IStartInteraction(InteractionStrategy, Interactor);
}

void UInteractableComponent::IBindToOnInteractionStarted_Implementation(const FOnInteractionStarted& Event)
{
	OnInteractionStartedInternal.AddUnique(Event);
}

void UInteractableComponent::IUnbindToOnInteractionStarted_Implementation(const FOnInteractionStarted& Event)
{
	OnInteractionStartedInternal.Remove(Event);	
}


void UInteractableComponent::IFinishInteraction_Implementation(AActor* Interactor)
{
	if (!IsValid(InteractionStrategy)) return;
	if (!IIsEnabled_Implementation()) return;
	bInteracted = false;
	OnInteractionFinishedInternal.Broadcast(Interactor, GetOwner());
	IInteractableInterface::Execute_IFinishInteraction(InteractionStrategy, Interactor);
}

void UInteractableComponent::IBindToOnInteractionFinished_Implementation(const FOnInteractionFinished& Event)
{
	OnInteractionFinishedInternal.AddUnique(Event);
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
	OnInteractionGoalAchievedInternal.AddUnique(Event);
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
	OnForceFinishInteractionInternal.AddUnique(Event);
}

