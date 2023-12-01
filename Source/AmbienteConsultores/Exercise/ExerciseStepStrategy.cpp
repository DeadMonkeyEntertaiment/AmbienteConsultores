// Fill out your copyright notice in the Description page of Project Settings.


#include "ExerciseStepStrategy.h"
#include "AmbienteConsultores/InteractionSystem/InteractableInterface.h"
#include "Components/BoxComponent.h"


class UInteractableComponent;

void UExerciseStepStrategy::SetupStepBindings_Implementation()
{
	SetStepEnable(true);
}

void UExerciseStepStrategy::CallOnStepStart_Implementation()
{
	OnStepStart.Broadcast(StepTag, SuccessFeedback, FailFeedback);
}

void UExerciseStepStrategy::CallOnStepFinished_Implementation(bool Success)
{
	OnStepFinish.Broadcast(StepTag, StepsToDisable, Success, Success? SuccessFeedback : FailFeedback);
}

void UExerciseStepStrategy::SetStepEnable_Implementation(bool Enable)
{
	bStepEnable = Enable;
	UBoxComponent* BoxComponent;
	UInteractableComponent* InteractableComponent;
	if (Enable)
	{
		InteractionStartedActivationReqHandler.BindDynamic(this, &UExerciseStepStrategy::OnInteractableInteractionStarted);
		InteractionGoalActivationReqHandler.BindDynamic(this, &UExerciseStepStrategy::OnInteractableInteractionGoalAchieved);
		ForceFinishInteractionActivationReqHandler.BindDynamic(this, &UExerciseStepStrategy::OnInteractableInteractionFinished);

		for (TSoftObjectPtr<ABaseInteractable> InteractActor: InteractActors)
		{
			if (!IsValid(InteractActor.Get())) return;
			
			InteractableComponent = InteractActor.Get()->FindComponentByClass<UInteractableComponent>();			
			
			IInteractableInterface::Execute_IBindToOnInteractionStarted(InteractableComponent, InteractionStartedActivationReqHandler);
			IInteractableInterface::Execute_IBindToOnInteractionGoalAchieved(InteractableComponent, InteractionGoalActivationReqHandler);			
			IInteractableInterface::Execute_IBindToOnInteractionFinished(InteractableComponent, ForceFinishInteractionActivationReqHandler);
		}
	
		for (TSoftObjectPtr<AExerciseBoxCollision> BoxCollider : BoxColliders)
		{
			BoxComponent = BoxCollider.Get()->FindComponentByClass<UBoxComponent>();
			BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &UExerciseStepStrategy::OnBoxBeginOverlap);
		}
		
	}
	else
	{
		for (TSoftObjectPtr<ABaseInteractable> InteractActor: InteractActors)
		{
			if (!IsValid(InteractActor.Get())) return;
			InteractableComponent = InteractActor.Get()->FindComponentByClass<UInteractableComponent>();		
			IInteractableInterface::Execute_IUnbindToOnInteractionStarted(InteractableComponent, InteractionStartedActivationReqHandler);
			IInteractableInterface::Execute_IUnbindToOnInteractionGoalAchieved(InteractableComponent, InteractionGoalActivationReqHandler);			
			IInteractableInterface::Execute_IUnbindToOnInteractionFinished(InteractableComponent, ForceFinishInteractionActivationReqHandler);
		}	
	
		for (TSoftObjectPtr<AExerciseBoxCollision> BoxCollider : BoxColliders)
		{
			BoxComponent = BoxCollider.Get()->FindComponentByClass<UBoxComponent>();
			BoxComponent->OnComponentBeginOverlap.RemoveDynamic(this, &UExerciseStepStrategy::OnBoxBeginOverlap);
		}
		
	}
	
}
