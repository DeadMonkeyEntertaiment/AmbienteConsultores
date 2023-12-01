// Fill out your copyright notice in the Description page of Project Settings.


#include "EvaluationSubsystem.h"
#include "AmbienteConsultores/Modules/DataAssets/ExerciseDataAsset.h"
#include "AmbienteConsultores/Modules/DataAssets/ModuleDataAsset.h"
#include "Kismet/GameplayStatics.h"

//Questionnaire
TArray<FQuestion> UEvaluationSubsystem::GetQuestions()
{
	return Questions;
}

void UEvaluationSubsystem::ResetQuestionnaire()
{	
	Questions.Empty();
}

//Activity
void UEvaluationSubsystem::StartActivity()
{
	CurrentExerciseNumber = 0;
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, SelectedModule->ModuleLevel);
}

void UEvaluationSubsystem::NextExercise()
{		
	CurrentExerciseNumber++;		
	if (!SelectedExercises.IsValidIndex(CurrentExerciseNumber)) return;
	ManageSubLevelsLoad();
}

void UEvaluationSubsystem::FinishActivity()
{	
	UGameplayStatics::OpenLevel(GWorld, EntryLevelName, false);
}

//Exercise
void UEvaluationSubsystem::StartExerciseEvaluation()
{
	if (!IsValid(GetCurrentExercise())) return;
	CurrentExerciseEvaluation.Exercise = GetCurrentExercise()->ExerciseTag;
	CurrentExerciseEvaluation.Step = ExercisesEvaluations.Num();
	CurrentExerciseEvaluation.Time = UGameplayStatics::GetTimeSeconds(GetWorld());
	CurrentExerciseEvaluation.repeats = 0; 
	CurrentExerciseEvaluation.win = true;
	ManageSubLevelsLoad();
}

UExerciseEvaluationDataAsset*  UEvaluationSubsystem::GetCurrentExerciseEvaluation()
{
	if (!GetCurrentExercise()) return nullptr;
	return GetCurrentExercise()->ExerciseEvaluationDataAsset;
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

void UEvaluationSubsystem::RetryExercise()
{
	if (!SelectedExercises.IsValidIndex(CurrentExerciseNumber)) return;
	LoadLevelIndex=0;
	UnloadWorlds = SelectedExercises[CurrentExerciseNumber]->ExerciseSublevels;		
	LoadWorlds = SelectedExercises[CurrentExerciseNumber]->ExerciseSublevels;
	UnloadNextStreamLevel();	
}

void UEvaluationSubsystem::FinishExerciseEvaluation(bool &ActivityFinished)
{
	CurrentExerciseEvaluation.Time = UGameplayStatics::GetTimeSeconds(GetWorld()) - CurrentExerciseEvaluation.Time;	
	ExercisesEvaluations.Add(CurrentExerciseEvaluation);
	ActivityFinished = !SelectedExercises.IsValidIndex(CurrentExerciseNumber+1);
}



//Load-unload StreamLevels
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

//Data
FString UEvaluationSubsystem::GetSelectedModuleId()
{
	return SelectedModule->ModuleID;
}

TArray<FExerciseEvaluation> UEvaluationSubsystem::GetExercisesEvaluations()
{
	return ExercisesEvaluations;
}

UExerciseDataAsset* UEvaluationSubsystem::GetCurrentExercise()
{
	if (SelectedExercises.IsValidIndex(CurrentExerciseNumber))
	{
		return SelectedExercises[CurrentExerciseNumber];	
	}
	return nullptr;
}

void UEvaluationSubsystem::SetSelectedModule(UModuleDataAsset* Module)
{
	SelectedModule = Module;
}

void UEvaluationSubsystem::AddExercisesToActivity(UExerciseDataAsset* ExerciseData)
{	
	Questions.Append(ExerciseData->Questions);
	SelectedExercises.AddUnique(ExerciseData);
}

