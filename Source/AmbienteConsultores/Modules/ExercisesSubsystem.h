// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ExercisesSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class AMBIENTECONSULTORES_API UExercisesSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable)
	void AddExercisesToTraining(TSoftObjectPtr<UWorld> Level);

	UFUNCTION(BlueprintCallable)
	void StartTraining();	
	
	UFUNCTION(BlueprintCallable)
	void NextExercise();

private:	
	UPROPERTY()
	TArray<TSoftObjectPtr<UWorld>> SelectedExercises;

	UPROPERTY()
	int32 CurrentExercise;
};
