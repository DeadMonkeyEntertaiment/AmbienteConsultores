// Fill out your copyright notice in the Description page of Project Settings.


#include "EvaluationSubsystem.h"
#include "AmbienteConsultores/Modules/DataAssets/ExerciseDataAsset.h"
#include "AmbienteConsultores/Modules/DataAssets/ModuleDataAsset.h"
#include "Kismet/GameplayStatics.h"

TArray<FQuestion> UEvaluationSubsystem::GetQuestions()
{
	return Questions;
}

void UEvaluationSubsystem::AddFailedAttempt()
{
	CurrentExerciseEvaluation.repeats++;
	if (CurrentExerciseEvaluation.repeats > 3)
	{
		CurrentExerciseEvaluation.win = false;
	}
}

void UEvaluationSubsystem::AddSuccessfulAttempt()
{
	
}

void UEvaluationSubsystem::ResetQuestionnaire()
{	
	Questions.Empty();
}

void UEvaluationSubsystem::SetSelectedModule(UModuleDataAsset* Module)
{
	SelectedModule = Module;
}

void UEvaluationSubsystem::StartExerciseEvaluation()
{
	if (!IsValid(GetCurrentExercise())) return;
	CurrentExerciseEvaluation.Exercise = GetCurrentExercise()->ExerciseTag;
	CurrentExerciseEvaluation.Step = 0;
	CurrentExerciseEvaluation.Time = UGameplayStatics::GetTimeSeconds(GetWorld());
	CurrentExerciseEvaluation.repeats = 0; 
	CurrentExerciseEvaluation.win = true;
	ManageSubLevelsLoad();
}

void UEvaluationSubsystem::FinishExerciseEvaluation(bool &ExerciesesFinished)
{
	CurrentExerciseEvaluation.Time = UGameplayStatics::GetTimeSeconds(GetWorld()) - CurrentExerciseEvaluation.Time;
	CurrentExerciseEvaluation.Step = ExercisesEvaluations.Num();
	ExercisesEvaluations.Add(CurrentExerciseEvaluation);
	NextExercise(ExerciesesFinished);
}

void UEvaluationSubsystem::AddExercisesToActivity(UExerciseDataAsset* ExerciseData)
{	
	Questions.Append(ExerciseData->Questions);
	SelectedExercises.AddUnique(ExerciseData);
}

void UEvaluationSubsystem::StartActivity()
{
	CurrentExerciseNumber = 0;
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, SelectedModule->ModuleLevel);
}

void UEvaluationSubsystem::NextExercise(bool &ActivityFinished)
{		
	CurrentExerciseNumber++;	
	ActivityFinished = !SelectedExercises.IsValidIndex(CurrentExerciseNumber);
	if (ActivityFinished) return;
	ManageSubLevelsLoad();
}

void UEvaluationSubsystem::ManageSubLevelsLoad()
{
	LoadLevelIndex = 0;
	if (CurrentExerciseNumber == 0)
	{
		LoadWorlds = SelectedExercises[CurrentExerciseNumber]->ExerciseSublevels;
		LoadNextStreamLevel();		
	}
	else
	{			
		UnloadWorlds = SelectedExercises[CurrentExerciseNumber-1]->ExerciseSublevels;		
		LoadWorlds = SelectedExercises[CurrentExerciseNumber]->ExerciseSublevels;
		UnloadNextStreamLevel();
	}
}

void UEvaluationSubsystem::UnloadNextStreamLevel()
{
	if (UnloadWorlds.IsValidIndex(LoadLevelIndex))
	{
		UnloadStreamLevel(UnloadWorlds[LoadLevelIndex]);
		LoadLevelIndex++;
	}
	else
	{
		LoadLevelIndex = 0;
		LoadNextStreamLevel();
	}
}

void UEvaluationSubsystem::UnloadStreamLevel(TSoftObjectPtr<UWorld> LoadWorld)
{
	FLatentActionInfo info;
	info.CallbackTarget = this;
	info.ExecutionFunction = "UnloadNextStreamLevel";
	info.UUID = 1;
	info.Linkage = 0;
	UGameplayStatics::UnloadStreamLevelBySoftObjectPtr(GetWorld(),LoadWorld, info, true);
	
}


void UEvaluationSubsystem::LoadNextStreamLevel()
{
	if (!LoadWorlds.IsValidIndex(LoadLevelIndex)) return;
	LoadStreamLevel(LoadWorlds[LoadLevelIndex]);
	LoadLevelIndex++;
}

void UEvaluationSubsystem::LoadStreamLevel(TSoftObjectPtr<UWorld> LoadWorld)
{
	FLatentActionInfo info;
	info.CallbackTarget = this;
	info.ExecutionFunction = "LoadNextStreamLevel";
	info.UUID = 1;
	info.Linkage = 0;
	UGameplayStatics::LoadStreamLevelBySoftObjectPtr(GetWorld(),LoadWorld, true, true, info);
}

UExerciseDataAsset* UEvaluationSubsystem::GetCurrentExercise()
{
	if (SelectedExercises.IsValidIndex(CurrentExerciseNumber))
	{
		return SelectedExercises[CurrentExerciseNumber];	
	}
	return nullptr;
}

void UEvaluationSubsystem::FinishActivity()
{	
	UGameplayStatics::OpenLevel(GWorld, EntryLevelName, false);
}

FString UEvaluationSubsystem::GetSelectedModuleId()
{
	return SelectedModule->ModuleID;
}

TArray<FExerciseEvaluation> UEvaluationSubsystem::GetExercisesEvaluations()
{
	return ExercisesEvaluations;
}


