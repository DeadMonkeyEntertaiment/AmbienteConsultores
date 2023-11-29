// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ADPCMAudioInfo.h"
#include "MissionStepBase.h"
#include "UObject/Object.h"
#include "ChangeSublevelMissionStep.generated.h"

/**
 * 
 */
UCLASS()
class UChangeSublevelMissionStep : public UMissionStepBase
{
	GENERATED_BODY()

public:
	UFUNCTION()	void OnJobEnded(TScriptInterface<ILevelStreamingJobInterface> Reference);
	void ChangeLevel(bool Reverse = false);
	virtual void Execute(AActor* InPlayerActor) override;
	virtual void Cancel() override;
private:
	UPROPERTY(EditDefaultsOnly) TArray<TSoftObjectPtr<UWorld>> LevelsToSwap;
	UPROPERTY(EditDefaultsOnly) bool bUnloadLevels = false;
	UPROPERTY(EditDefaultsOnly) bool bWaitLevelsChangedToEndStep = true;
	UPROPERTY(EditDefaultsOnly, meta=(EditCondition="!bUnloadLevels", EditConditionHides)) bool bMakeLevelsVisibleAfterLoad = true;
	UPROPERTY(EditDefaultsOnly) bool bLevelsBlockWhileChanging = true;

	UPROPERTY() bool bWaitingSubsystemRelease;
	UPROPERTY() bool bWaitingChangeProcess;
	UPROPERTY() bool bRevertAfterProcessEnds;
};
