// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelStreamingJob.h"
#include "UObject/Object.h"
#include "LevelStreamingLoaderSubsystem.generated.h"

/**
 * Subsystem for level streaming processes handling.
 */
UCLASS()
class ULevelStreamingLoaderSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable) bool IsProcessRunning(){return IsValid(ActiveJob);};

	UFUNCTION(BlueprintCallable) TScriptInterface<ILevelStreamingJobInterface> QueueLoadStreamingLevel(TSoftObjectPtr<UWorld> Level, bool bVisibleAfterLoading, bool bBlockOnLoad);
	UFUNCTION(BlueprintCallable) TScriptInterface<ILevelStreamingJobInterface> QueueUnloadStreamingLevel(TSoftObjectPtr<UWorld> Level, bool bBlockOnLoad);
	UFUNCTION(BlueprintCallable) TScriptInterface<ILevelStreamingJobInterface> QueueLoadStreamingLevels(TArray<TSoftObjectPtr<UWorld>> Level, bool bVisibleAfterLoading, bool bBlockOnLoad);
	UFUNCTION(BlueprintCallable) TScriptInterface<ILevelStreamingJobInterface> QueueUnloadStreamingLevels(TArray<TSoftObjectPtr<UWorld>> Level, bool bBlockOnLoad);
	
private:

	UFUNCTION() void ExecuteJob();
	UFUNCTION()	void OnJobEnd(TScriptInterface<ILevelStreamingJobInterface> JobReference);
	
	UPROPERTY() TArray<ULevelStreamingJob*> JobsQueue;
	UPROPERTY() ULevelStreamingJob* ActiveJob;
};
