// Fill out your copyright notice in the Description page of Project Settings.


#include "ExercisesSubsystem.h"

#include "Kismet/GameplayStatics.h"

void UExercisesSubsystem::AddExercisesToTraining(TSoftObjectPtr<UWorld> Level)
{
	SelectedExercises.AddUnique(Level);
}

void UExercisesSubsystem::StartTraining()
{
	CurrentExercise = 0;
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, SelectedExercises[CurrentExercise]);	
}

void UExercisesSubsystem::NextExercise()
{
	CurrentExercise++;
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, SelectedExercises[CurrentExercise]);	
}