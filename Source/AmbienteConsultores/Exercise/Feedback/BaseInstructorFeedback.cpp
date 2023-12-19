// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseInstructorFeedback.h"
#include "AmbienteConsultores/Exercise/Instructor/InstructorInterface.h"


void UBaseInstructorFeedback::DoFeedback_Implementation(AActor* Instructor, AActor* Player)
{
	Super::DoFeedback_Implementation(Instructor, Player);
	if (!IsValid(Instructor))return;
	UActorComponent* InstructorComponent = Instructor->FindComponentByInterface(UInstructorInterface::StaticClass());

	FOnInstructorFeedbackDone FeedbackDoneActivationReqHandler;
	FeedbackDoneActivationReqHandler.BindDynamic(this, &UBaseInstructorFeedback::OnFeedbackDone);
	IInstructorInterface::Execute_IBindToOnInstructorFeedbackDone(InstructorComponent, FeedbackDoneActivationReqHandler);
	
	IInstructorInterface::Execute_IDoInstructorFeedback(InstructorComponent, InstructorFeedback);
}
