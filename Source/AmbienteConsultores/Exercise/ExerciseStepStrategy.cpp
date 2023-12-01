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
	UBoxComponent* BoxComponent;
	if (Enable)
	{

		for (TSoftObjectPtr<ABaseInteractable> InteractActor: InteractActors)
		{
			if (!IsValid(InteractActor.Get())) return;
			UInteractableComponent* InteractableComponent = InteractActor.Get()->FindComponentByClass<UInteractableComponent>();
			
			InteractionStartedActivationReqHandler.BindDynamic(this, &UExerciseStepStrategy::OnInteractionStarted);
			IInteractableInterface::Execute_IBindToOnInteractionStarted(InteractableComponent, InteractionStartedActivationReqHandler);

			InteractionGoalActivationReqHandler.BindDynamic(this, &UExerciseStepStrategy::OnInteractionGoalAchieved);
			IInteractableInterface::Execute_IBindToOnInteractionGoalAchieved(InteractableComponent, InteractionGoalActivationReqHandler);			
		
			ForceFinishInteractionActivationReqHandler.BindDynamic(this, &UExerciseStepStrategy::OnInteractionFinished);
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
			UInteractableComponent* InteractableComponent = InteractActor.Get()->FindComponentByClass<UInteractableComponent>();

			InteractionStartedActivationReqHandler.Unbind();
			InteractionStartedActivationReqHandler.Clear();
			IInteractableInterface::Execute_IUnbindToOnInteractionStarted(InteractableComponent, InteractionStartedActivationReqHandler);

			InteractionGoalActivationReqHandler.Unbind();
			InteractionGoalActivationReqHandler.Clear();
			IInteractableInterface::Execute_IUnbindToOnInteractionGoalAchieved(InteractableComponent, InteractionGoalActivationReqHandler);			
		
			ForceFinishInteractionActivationReqHandler.Unbind();
			ForceFinishInteractionActivationReqHandler.Clear();
			IInteractableInterface::Execute_IUnbindToOnInteractionFinished(InteractableComponent, ForceFinishInteractionActivationReqHandler);
		}	
	
		for (TSoftObjectPtr<AExerciseBoxCollision> BoxCollider : BoxColliders)
		{
			BoxComponent = BoxCollider.Get()->FindComponentByClass<UBoxComponent>();
			BoxComponent->OnComponentBeginOverlap.RemoveDynamic(this, &UExerciseStepStrategy::OnBoxBeginOverlap);
		}
		
	}
	
}
