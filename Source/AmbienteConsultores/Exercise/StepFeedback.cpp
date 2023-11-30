// Fill out your copyright notice in the Description page of Project Settings.


#include "StepFeedback.h"

#include "Instructor/InstructorInterface.h"
#include "Instructor/InstructorLogicComponent.h"

void UStepFeedback::DoFeedback_Implementation(AActor* Instructor, AActor* Player)
{
	if (!IsValid(Instructor))return;
	IInstructorInterface::Execute_InstructorFeedback(Instructor->FindComponentByClass<UInstructorLogicComponent>(), InstructorDialog);
}
