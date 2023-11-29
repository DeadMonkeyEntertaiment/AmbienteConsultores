// Fill out your copyright notice in the Description page of Project Settings.


#include "SequentialMissionStep.h"

void USequentialMissionStep::Execute(AActor* InPlayerActor)
{
	Super::Execute(InPlayerActor);
	//If there aren't steps to execute, we finished.
	if(Steps.IsEmpty())
	{
		EndExecution(true);
		return;
	}
	ExecuteNextStep();
}

void USequentialMissionStep::Cancel()
{
	//In order to cancel a sequential step, we have to cancel the active step and wait until it broadcast that finished.
	if(IsValid(GetActiveStep()))
	{
		GetActiveStep()->Cancel();
		GetActiveStep()->ConditionalBeginDestroy();
	}
}

void USequentialMissionStep::ExecuteNextStep()
{
	UMissionStepBase* StepBase = GetActiveStep();
	if (!ensureMsgf(IsValid(StepBase), TEXT("%s doesn't have a valid Active Step"), *this->GetName())) return;
	StepBase->OnStepDone.AddDynamic(this, &USequentialMissionStep::OnStepExecutionDone);
	StepBase->Execute(PlayerActor);
}
void USequentialMissionStep::OnStepExecutionDone(UMissionStepBase* Step, bool bSuccess)
{
	GetActiveStep()->OnStepDone.RemoveDynamic(this, &USequentialMissionStep::OnStepExecutionDone);
	//If the step was cancelled or failed, then we have to end the execution of the sequential step.
	// Note that we dont broadcast OnSubstepDone. <Should we?>
	if(!bSuccess)
	{
		Super::Cancel();
		return;
	}
	
	if(OnSubstepDone.IsBound())
	{
		OnSubstepDone.Broadcast(Step, bSuccess);
	}

	CurrentIndex++;
	if(Steps.Num() != CurrentIndex)
	{
		ExecuteNextStep();
	}else
	{
		CurrentIndex = 0;
		EndExecution(true);
	}
	
}

UMissionStepBase* USequentialMissionStep::GetActiveStep()
{
	return Steps[CurrentIndex];
}
