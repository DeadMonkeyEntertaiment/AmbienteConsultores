// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActivitySubsystem.generated.h"

class UExerciseDataAsset;
/**
 * 
 */
UCLASS()
class AMBIENTECONSULTORES_API UActivitySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable)
	void AddExercisesToActivity(UExerciseDataAsset* ExerciseData);

	UFUNCTION(BlueprintCallable)
	void StartActivity();	
	
	UFUNCTION(BlueprintCallable)
	bool NextExercise();
	
	UFUNCTION(BlueprintCallable)
	UExerciseDataAsset* GetCurrentExercise();

private:	
	UPROPERTY()
	TArray<UExerciseDataAsset*> SelectedExercises;

	UPROPERTY()
	int32 CurrentExercise;
};
