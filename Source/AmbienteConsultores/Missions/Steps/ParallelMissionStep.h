// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MissionStepBase.h"
#include "UObject/Object.h"
#include "ParallelMissionStep.generated.h"

/**
 * 
 */
UCLASS()
class UParallelMissionStep : public UMissionStepBase
{
	GENERATED_BODY()

public:
	virtual void Execute(AActor* InPlayerActor) override;
	virtual void Cancel() override;
	virtual void EndExecution(bool bSuccess) override;
	UFUNCTION() void CancelRunningSteps();
	
	UFUNCTION() void OnSubstepDone(UMissionStepBase* Step,bool bSuccess);
private:
	UPROPERTY(EditDefaultsOnly, Instanced) TArray<TObjectPtr<UMissionStepBase>> Steps;
	UPROPERTY(EditDefaultsOnly) bool bEndOnFirstStepDone = true;
	UPROPERTY() TArray<TObjectPtr<UMissionStepBase>> RunningSteps;

	UPROPERTY() bool bIsCancelling = false;
	UPROPERTY() bool bIsEndingExecution = false;
};
