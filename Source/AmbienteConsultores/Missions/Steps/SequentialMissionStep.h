// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MissionStepBase.h"
#include "UObject/Object.h"
#include "SequentialMissionStep.generated.h"

/**
 * 
 */
UCLASS()
class USequentialMissionStep : public UMissionStepBase
{
	GENERATED_BODY()
public:
	//Parent methods
	virtual void Execute(AActor* InPlayerActor) override;
	virtual void Cancel() override;

	
	UFUNCTION() void ExecuteNextStep();
	UFUNCTION() void OnStepExecutionDone(UMissionStepBase* Step, bool bSuccess);
	UFUNCTION() UMissionStepBase* GetActiveStep();
	
	UFUNCTION() void SetSteps(TArray<UMissionStepBase*> InSteps){ Steps = InSteps;};

	UPROPERTY() FOnStepDone OnSubstepDone;
private:
	UPROPERTY(EditDefaultsOnly, Instanced)
	TArray<UMissionStepBase*> Steps;

	UPROPERTY()
	int CurrentIndex;
};
