// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivitySubsystem.h"

#include "DataAssets/ExerciseDataAsset.h"
#include "Kismet/GameplayStatics.h"

void UActivitySubsystem::AddExercisesToActivity(UExerciseDataAsset* ExerciseData)
{
	SelectedExercises.AddUnique(ExerciseData);
}

void UActivitySubsystem::StartActivity()
{
	CurrentExercise = 0;
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, SelectedExercises[CurrentExercise]->ExerciseLevel);	
}

bool UActivitySubsystem::NextExercise()
{
	CurrentExercise++;
	if (!SelectedExercises.IsValidIndex(CurrentExercise)) return false;			
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, SelectedExercises[CurrentExercise]->ExerciseLevel);
	return true;
}

UExerciseDataAsset* UActivitySubsystem::GetCurrentExercise()
{
	if (SelectedExercises.IsValidIndex(CurrentExercise))
	{
		return SelectedExercises[CurrentExercise];	
	}
	return nullptr;
}
