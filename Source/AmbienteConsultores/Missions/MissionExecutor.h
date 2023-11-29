// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Graph/MissionGraph.h"
#include "Steps/MissionStepBase.h"
#include "Steps/SequentialMissionStep.h"
#include "UObject/Object.h"
#include "MissionExecutor.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExecutionFinished, bool, bSuccess);

/**
 * 
 */
UCLASS(BlueprintType)
class UMissionExecutor : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION() void StartExecution(AActor* InPlayerActor, TArray<UMissionStepBase*> MissionSteps);
	UFUNCTION() void StartGraphExecution(AActor* InPlayerActor, UMissionGraph* MissionGraph);
	UFUNCTION() void OnStepExecutionDone(UMissionStepBase* Step, bool bSuccess);
	UFUNCTION()void OnExecutionDone(UMissionStepBase* Step, bool bSuccess);
	UFUNCTION() void CancelExecution();
	UPROPERTY() FOnExecutionFinished OnExecutionFinished;
	UPROPERTY() FOnStepDone OnStepDone;
private:
	UPROPERTY()	TObjectPtr<USequentialMissionStep> MainStep;

	UFUNCTION() TArray<UMissionStepBase*> GetStepsListFromGraph(UMissionGraph* Graph);
	
};
