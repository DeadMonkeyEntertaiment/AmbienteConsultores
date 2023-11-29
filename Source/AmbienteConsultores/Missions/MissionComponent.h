// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MissionDataFragment.h"
#include "MissionExecutor.h"
#include "Components/ActorComponent.h"
#include "MissionComponent.generated.h"

class UAudioComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMissionStarted, AActor*, EventActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMissionEnded, AActor*, EventActor, bool, bIsCompleted);



UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UMissionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMissionComponent();

	UPROPERTY(BlueprintAssignable) FMissionStarted OnMissionStarted;
	UPROPERTY(BlueprintAssignable) FMissionEnded OnMissionEnded;
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
protected:
	virtual void BeginPlay() override;

protected:
	UFUNCTION() void LoadMissionStates();
	UFUNCTION() void OnStartTriggerActivated(FTriggerInteractionInfo Info);
	UFUNCTION() void OnEndTriggerActivated(FTriggerInteractionInfo Info);
	UFUNCTION() void UpdateBlocking(bool Activate);
	UFUNCTION(BlueprintCallable) void PrepareMission();
	UFUNCTION() void StartMission();
	UFUNCTION() void GiveReward();
	UFUNCTION() void EndMission(bool Completed);
	UFUNCTION() void CheckChangeLevel();
	UFUNCTION() void UpdateMap();
	UFUNCTION() void OnSublevelsDeactivated(TScriptInterface<ILevelStreamingJobInterface> JobReference);
	UFUNCTION() void OnSublevelsActivated(TScriptInterface<ILevelStreamingJobInterface> JobReference);
	UFUNCTION() void OnSublevelsReverted(TScriptInterface<ILevelStreamingJobInterface> JobReference);
	UFUNCTION() void OnExecutionDone(bool Completed);
	UFUNCTION() bool PlaySequence(ULevelSequence* Sequence, bool bBlockDefaultSkipPrompt = false);
	UFUNCTION() void OnSequenceFinished();
	UPROPERTY(BlueprintReadOnly) UMissionDataFragment* DataFragmentRef;

private:
	UFUNCTION() void SetState(EMissionState NewState);
	UFUNCTION()	void OnMissionsListUpdated();
	UPROPERTY() TEnumAsByte<EMissionState> State;
	UPROPERTY() bool bIsExecutingIntroSequence;
	UPROPERTY() bool bIsMissionActive;
	UPROPERTY() TObjectPtr<UMissionExecutor> Executor;
	UPROPERTY() ALevelSequenceActor* SequencePlayerActor;
	UPROPERTY() AActor* PlayerCharacter;
	UPROPERTY() UAudioComponent* CurrentAudioComponent;
};
