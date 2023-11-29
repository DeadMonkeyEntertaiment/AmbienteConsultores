// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MissionDataFragment.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "MissionSubsystem.generated.h"

class UMissionComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMissionListUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMissionCompleted, FGameplayTag, AscensionEventTag);

USTRUCT(BlueprintType)
struct FMissionData
{
	GENERATED_BODY()

	UPROPERTY(SaveGame) FGameplayTag MissionTag;
	UPROPERTY(SaveGame) bool bRewardClaimed = false;
	UPROPERTY(SaveGame, BlueprintReadOnly) TEnumAsByte<EMissionState> MissionState = EMissionState::MS_UNDISCOVERED;
	UPROPERTY() UMissionDataFragment* DataFragmentRef = nullptr;
};

/**
 * 
 */
UCLASS()
class  UMissionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	void UpdateEventState(FGameplayTag MissionTag, EMissionState NewState);

	UFUNCTION(BlueprintCallable)
	TArray<FMissionData> GetEventStates();
	
	bool GetMissionState(FGameplayTag MissionTag, FMissionData& MissionData);

	void UpdateMissionsList(TArray<FMissionData> Missions);

	UPROPERTY(BlueprintAssignable)
	FMissionListUpdated OnMissionListUpdated;

	UPROPERTY(BlueprintAssignable)
	FMissionCompleted OnMissionCompleted;
	
private:
	void LoadMissionsFromAssets();

	UPROPERTY()
	TMap<FGameplayTag, FMissionData> MissionsData;

	UPROPERTY()
	TArray<UObject*> RawDataAssets;
};
