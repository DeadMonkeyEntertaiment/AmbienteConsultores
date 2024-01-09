// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseStepFeedback.h"


void UBaseStepFeedback::OnFeedbackDone_Implementation()
{
	OnStepFeedbackDone.Broadcast(this);
}

void UBaseStepFeedback::DoFeedback_Implementation(AActor* instructor, AActor* player)
{
	Instructor = instructor;
	Player = player;
}
