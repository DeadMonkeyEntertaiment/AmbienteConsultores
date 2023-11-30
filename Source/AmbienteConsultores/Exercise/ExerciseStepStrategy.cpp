// Fill out your copyright notice in the Description page of Project Settings.


#include "ExerciseStepStrategy.h"

#include "AmbienteConsultores/InteractionSystem/InteractableInterface.h"
#include "Components/BoxComponent.h"


class UInteractableComponent;

void UExerciseStepStrategy::SetupStepBindings_Implementation()
{

	for (TSoftObjectPtr<ABaseInteractable> InteractActor: InteractActors)
	{
		if (!IsValid(InteractActor.Get())) return;
		UInteractableComponent* InteractableComponent = InteractActor.Get()->FindComponentByClass<UInteractableComponent>();

		FOnInteractionStart InteractionStartedActivationReqHandler;			
		InteractionStartedActivationReqHandler.BindDynamic(this, &UExerciseStepStrategy::OnInteractionStarted);
		IInteractableInterface::Execute_IBindToOnInteractionStarted(InteractableComponent, InteractionStartedActivationReqHandler);

		FOnInteractionGoalAchieved InteractionGoalActivationReqHandler;	
		InteractionGoalActivationReqHandler.BindDynamic(this, &UExerciseStepStrategy::OnInteractionGoalAchieved);
		IInteractableInterface::Execute_IBindToOnInteractionGoalAchieved(InteractableComponent, InteractionGoalActivationReqHandler);		
		
		FOnInteractionFinished ForceFinishInteractionActivationReqHandler;
		ForceFinishInteractionActivationReqHandler.BindDynamic(this, &UExerciseStepStrategy::OnInteractionFinished);
		IInteractableInterface::Execute_IBindToOnInteractionFinished(InteractableComponent, ForceFinishInteractionActivationReqHandler);
	}
	
	for (TSoftObjectPtr<AExerciseBoxCollision> BoxCollider : BoxColliders)
	{
		UBoxComponent* BoxComponent = BoxCollider.Get()->FindComponentByClass<UBoxComponent>();
		BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &UExerciseStepStrategy::OnBoxBeginOverlap);
	}
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
	IsStepEnable = Enable;
}
