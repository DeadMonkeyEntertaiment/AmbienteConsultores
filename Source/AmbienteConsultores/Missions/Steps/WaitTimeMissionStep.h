// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MissionStepBase.h"
#include "UObject/Object.h"
#include "WaitTimeMissionStep.generated.h"

/**
 * 
 */
UCLASS()
class UWaitTimeMissionStep : public UMissionStepBase
{
	GENERATED_BODY()

public:
	virtual void Execute(AActor* InPlayerActor) override;
	virtual void Cancel() override;
#if WITH_EDITOR
	virtual FText GetNodeTitle() const override;
#endif

private:
	UPROPERTY(EditDefaultsOnly) float TimeToWait = 1;
	UPROPERTY() FTimerHandle TimerHandle;
};
