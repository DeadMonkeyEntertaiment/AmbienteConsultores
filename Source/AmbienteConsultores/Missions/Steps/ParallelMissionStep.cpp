// Fill out your copyright notice in the Description page of Project Settings.


#include "ParallelMissionStep.h"

void UParallelMissionStep::Execute(AActor* InPlayerActor)
{
	Super::Execute(InPlayerActor);
	bIsEndingExecution = false;
	RunningSteps.Empty();
	if (Steps.IsEmpty()) EndExecution(true);

   	for (auto Step : Steps)
	{
		// SASSERT(GetOuter()->GetOuter(), IsValid(Step), , "Not Valid Step in %s step, in Steps %s", *this->GetName(), *GetOuter()->GetName());
		Step->OnStepDone.AddUniqueDynamic(this, &UParallelMissionStep::OnSubstepDone);
		RunningSteps.Add(Step);
		Step->Execute(InPlayerActor);
	}
}

void UParallelMissionStep::Cancel()
{
	bIsCancelling = true;
	CancelRunningSteps();
}

void UParallelMissionStep::EndExecution(bool bSuccess)
{
	bIsEndingExecution = false;
	bIsCancelling = false;
	RunningSteps.Empty();
	Super::EndExecution(bSuccess);
}

void UParallelMissionStep::CancelRunningSteps()
{
	TArray<TObjectPtr<UMissionStepBase>> TempArray = RunningSteps;
	for (auto Step : TempArray)
	{
		Step->Cancel();
	}
}

void UParallelMissionStep::OnSubstepDone(UMissionStepBase* Step, bool bSuccess)
{
	Step->OnStepDone.RemoveDynamic(this, &UParallelMissionStep::OnSubstepDone);
	RunningSteps.Remove(Step);
	// If substep failed, we're not cancelling and we're not ending the process, then this step fails.
	if(!bSuccess && !bIsCancelling && !bIsEndingExecution)
	{
		Cancel();
		return;
	}

	//Step ended.
	if(RunningSteps.Num() == 0)
	{
		EndExecution(bSuccess || bIsEndingExecution);
		return;
	}
	
	if(bEndOnFirstStepDone && !bIsEndingExecution)
	{
		bIsEndingExecution = true;
		CancelRunningSteps();
	}

}
