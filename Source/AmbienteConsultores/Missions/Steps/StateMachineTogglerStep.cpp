// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachineTogglerStep.h"

#include <SMStateMachineComponent.h>


void UStateMachineTogglerStep::Execute(AActor* InPlayerActor)
{
	Super::Execute(InPlayerActor);

	if (Mannequins.Num() == 0)
	{
		EndExecution(false);
		return;
	}
	for (auto CurrentMannequin : Mannequins)
	{
		USMStateMachineComponent* StateMachineComponent = CurrentMannequin->FindComponentByClass<
			USMStateMachineComponent>();
		if (!IsValid(StateMachineComponent))
			continue;

		if (bShouldStartStateMachine)
			StateMachineComponent->Start();
		else
			StateMachineComponent->Stop();
	}

	EndExecution(true);
}
