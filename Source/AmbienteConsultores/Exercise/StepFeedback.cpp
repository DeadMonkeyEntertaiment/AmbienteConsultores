// Fill out your copyright notice in the Description page of Project Settings.


#include "StepFeedback.h"
#include "Instructor/InstructorInterface.h"

void UStepFeedback::DoFeedback_Implementation(AActor* Instructor, AActor* Player)
{
	if (!IsValid(Instructor))return;
	UActorComponent* InstructorComponent = Instructor->FindComponentByInterface(UInstructorInterface::StaticClass());

	FOnInstructorFeedbackDone FeedbackDoneActivationReqHandler;
	FeedbackDoneActivationReqHandler.BindDynamic(this, &UStepFeedback::OnFeedbackDone);
	IInstructorInterface::Execute_IBindToOnInstructorFeedbackDone(InstructorComponent, FeedbackDoneActivationReqHandler);
	
	IInstructorInterface::Execute_IDoInstructorFeedback(InstructorComponent, InstructorFeedback);
}

void UStepFeedback::OnFeedbackDone_Implementation()
{
	OnStepFeedbackDone.Broadcast();
}
