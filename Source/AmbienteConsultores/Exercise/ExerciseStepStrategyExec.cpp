// Fill out your copyright notice in the Description page of Project Settings.


#include "ExerciseStepStrategyExec.h"

#include "ExerciseStepStrategyDef.h"
#include "AmbienteConsultores/InteractionSystem/InteractableInterface.h"
#include "Components/BoxComponent.h"
#include "Feedback/FeedbackDataAsset.h"
#include "Kismet/GameplayStatics.h"


class UInteractableComponent;

void UExerciseStepStrategyExec::SetupStep_Implementation(APawn* playerPawn, UExerciseStepStrategyDef* Def)
{
	PlayerPawn = playerPawn;	
	StepTag = Def->StepTag;
	Autostart = Def->Autostart;
	InteractActors = Def->InteractActors;
	BoxColliders = Def->BoxColliders;
	AdditionalActors = Def->AdditionalActors;
	FeedbackDA = Def->FeedbackDA;
	AutoDisableAfterFinished = Def->AutoDisableAfterFinished;	
	AutoDisableInteractablesAfterFinished = Def->AutoDisableInteractablesAfterFinished;	
	StepsToDisableOnStart = Def->StepsToDisableOnStart;
	StepsToDisableOnFinish = Def->StepsToDisableOnFinish;	
	ChangeSublevel = Def->ChangeSublevel;
	StepSublevel = Def->StepSublevel;
	SublevelPlayerStart = Def->SublevelPlayerStart;
	SetStepAsNewReset = Def-> SetStepAsNewReset;
	
	SetStepEnable(true, true);
}


void UExerciseStepStrategyExec::CallOnStepStart_Implementation()
{
	OnStepStart.Broadcast(StepTag, StepsToDisableOnStart, FeedbackDA->StepStartFeedback, FeedbackDA->StepFinishedFailFeedback, FeedbackDA->StepFinishedDelayedFailFeedback);	
}

void UExerciseStepStrategyExec::CallOnStepFinished_Implementation(bool Success)
{
	OnStepFinish.Broadcast(StepTag, StepsToDisableOnFinish, Success, Success? FeedbackDA->StepFinishedSuccessFeedback : FeedbackDA->StepFinishedFailFeedback, FeedbackDA->StepFinishedDelayedFailFeedback);
	if (AutoDisableAfterFinished)
	{
		SetStepEnable_Implementation(false, AutoDisableInteractablesAfterFinished);
	}
}

void UExerciseStepStrategyExec::SetStepEnable_Implementation(bool Enable, bool PropagateToInteracts)
{	
	bStepEnable = Enable;
	UBoxComponent* BoxComponent;
	UInteractableComponent* InteractableComponent;	
	
	if (Enable)
	{
		InteractionStartedActivationReqHandler.BindDynamic(this, &UExerciseStepStrategyExec::OnInteractableInteractionStarted);
		InteractionGoalActivationReqHandler.BindDynamic(this, &UExerciseStepStrategyExec::OnInteractableInteractionGoalAchieved);
		ForceFinishInteractionActivationReqHandler.BindDynamic(this, &UExerciseStepStrategyExec::OnInteractableInteractionFinished);

		for (TSoftObjectPtr<ABaseInteractable> InteractActor: InteractActors)
		{
			if (!IsValid(InteractActor.Get())) return;
			
			InteractableComponent = InteractActor.Get()->FindComponentByClass<UInteractableComponent>();

			if (PropagateToInteracts) IInteractableInterface::Execute_ISetEnabled(InteractableComponent, true);
			
			IInteractableInterface::Execute_IBindToOnInteractionStarted(InteractableComponent, InteractionStartedActivationReqHandler);
			IInteractableInterface::Execute_IBindToOnInteractionGoalAchieved(InteractableComponent, InteractionGoalActivationReqHandler);			
			IInteractableInterface::Execute_IBindToOnInteractionFinished(InteractableComponent, ForceFinishInteractionActivationReqHandler);
		}
	
		for (TSoftObjectPtr<AExerciseBoxCollision> BoxCollider : BoxColliders)
		{
			BoxComponent = BoxCollider.Get()->FindComponentByClass<UBoxComponent>();
			BoxComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &UExerciseStepStrategyExec::OnBoxBeginOverlap);
		}
		
	}
	else
	{
		for (TSoftObjectPtr<ABaseInteractable> InteractActor: InteractActors)
		{
			if (!IsValid(InteractActor.Get())) return;
			
			InteractableComponent = InteractActor.Get()->FindComponentByClass<UInteractableComponent>();
			
			InteractionStartedActivationReqHandler.Unbind();
			InteractionGoalActivationReqHandler.Unbind();
			ForceFinishInteractionActivationReqHandler.Unbind();
			
			if (PropagateToInteracts) IInteractableInterface::Execute_ISetEnabled(InteractableComponent, false);

			IInteractableInterface::Execute_IUnbindToOnInteractionStarted(InteractableComponent, InteractionStartedActivationReqHandler);
			IInteractableInterface::Execute_IUnbindToOnInteractionGoalAchieved(InteractableComponent, InteractionGoalActivationReqHandler);			
			IInteractableInterface::Execute_IUnbindToOnInteractionFinished(InteractableComponent, ForceFinishInteractionActivationReqHandler);
		}	
	
		for (TSoftObjectPtr<AExerciseBoxCollision> BoxCollider : BoxColliders)
		{
			BoxComponent = BoxCollider.Get()->FindComponentByClass<UBoxComponent>();
			BoxComponent->OnComponentBeginOverlap.RemoveDynamic(this, &UExerciseStepStrategyExec::OnBoxBeginOverlap);
		}		
	}	
}


void UExerciseStepStrategyExec::AutostartStep_Implementation()
{
	CallOnStepStart();
}

void UExerciseStepStrategyExec::OnStartFeedbackDone_Implementation()
{
}
