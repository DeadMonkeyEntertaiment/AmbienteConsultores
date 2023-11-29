// Fill out your copyright notice in the Description page of Project Settings.


#include "MissionExecutor.h"

#include "Steps/SequentialMissionStep.h"

void UMissionExecutor::StartExecution(AActor* InPlayerActor, TArray<UMissionStepBase*> MissionSteps)
{
	ensure(InPlayerActor);
	//We delegate the responsibility of execution to a Sequential Mission step.
	if(!IsValid(MainStep)) MainStep = NewObject<USequentialMissionStep>(this);
	MainStep->OnStepDone.AddDynamic(this, &UMissionExecutor::OnExecutionDone);
	MainStep->OnSubstepDone.AddDynamic(this, &UMissionExecutor::OnStepExecutionDone);
	MainStep->SetSteps(MissionSteps);
	MainStep->Execute(InPlayerActor);
}

void UMissionExecutor::StartGraphExecution(AActor* InPlayerActor, UMissionGraph* MissionGraph)
{
	
	ensure(InPlayerActor);
	ensure(MissionGraph);
	//We delegate the responsibility of execution to a Sequential Mission step.
	if(!IsValid(MainStep)) MainStep = NewObject<USequentialMissionStep>(this);
	MainStep->OnStepDone.AddDynamic(this, &UMissionExecutor::OnExecutionDone);
	MainStep->OnSubstepDone.AddDynamic(this, &UMissionExecutor::OnStepExecutionDone);
	MainStep->SetSteps(GetStepsListFromGraph(MissionGraph));
	MainStep->Execute(InPlayerActor);
}

void UMissionExecutor::OnStepExecutionDone(UMissionStepBase* Step, bool bSuccess)
{
	//This executes when a substep of the MainStep is done.
	if(OnStepDone.IsBound()) OnStepDone.Broadcast(Step, bSuccess);
}

void UMissionExecutor::OnExecutionDone(UMissionStepBase* Step, bool bSuccess)
{
	MainStep->OnStepDone.RemoveDynamic(this, &UMissionExecutor::OnExecutionDone);
	MainStep->OnSubstepDone.RemoveDynamic(this, &UMissionExecutor::OnStepExecutionDone);
	//This executes when the MainStep is done.
	if(OnExecutionFinished.IsBound()) OnExecutionFinished.Broadcast(bSuccess);
	if(IsValid(MainStep)) MainStep->ConditionalBeginDestroy();
}
void UMissionExecutor::CancelExecution()
{
	if(IsValid(MainStep))
	{
		MainStep->Cancel();
		if(IsValid(MainStep)) MainStep->ConditionalBeginDestroy();
	}
}

TArray<UMissionStepBase*> UMissionExecutor::GetStepsListFromGraph(UMissionGraph* Graph)
{
	TArray<UMissionStepBase*> ResultList;

	for(auto Node: Graph->GetOrderedList())
		ResultList.Push(Cast<UMissionStepBase>(Node));

	return ResultList;
}
