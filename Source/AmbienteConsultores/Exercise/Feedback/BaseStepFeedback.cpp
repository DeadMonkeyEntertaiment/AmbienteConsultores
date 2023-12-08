// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseStepFeedback.h"
#include "AmbienteConsultores/Exercise/Instructor/InstructorInterface.h"

void UBaseStepFeedback::DoFeedback_Implementation(AActor* Instructor, AActor* Player)
{
	if (!IsValid(Instructor))return;
	UActorComponent* InstructorComponent = Instructor->FindComponentByInterface(UInstructorInterface::StaticClass());

	FOnInstructorFeedbackDone FeedbackDoneActivationReqHandler;
	FeedbackDoneActivationReqHandler.BindDynamic(this, &UBaseStepFeedback::OnFeedbackDone);
	IInstructorInterface::Execute_IBindToOnInstructorFeedbackDone(InstructorComponent, FeedbackDoneActivationReqHandler);
	
	IInstructorInterface::Execute_IDoInstructorFeedback(InstructorComponent, InstructorFeedback);
}

void UBaseStepFeedback::OnFeedbackDone_Implementation()
{
	OnStepFeedbackDone.Broadcast();
}
