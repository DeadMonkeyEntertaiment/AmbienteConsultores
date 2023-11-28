// Fill out your copyright notice in the Description page of Project Settings.


#include "EvaluationSubsystem.h"
#include "AmbienteConsultores/Modules/DataAssets/ExerciseDataAsset.h"
#include "Kismet/GameplayStatics.h"

TArray<FQuestion> UEvaluationSubsystem::GetQuestions()
{
	return Questions;
}

void UEvaluationSubsystem::StoreQuestionnaireScore(const int32 evaluationScore)
{
	QuestionnaireScore = evaluationScore;
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
	QuestionnaireScore =0;
	Questions.Empty();
}

void UEvaluationSubsystem::SetSelectedModule(const EModule Module)
{
	SessionResults.SelectedModule = Module;
}

void UEvaluationSubsystem::StartExerciseEvaluation()
{
	if (!IsValid(GetCurrentExercise())) return;
	CurrentExerciseEvaluation.Exercise = GetCurrentExercise()->Exercise;
	CurrentExerciseEvaluation.Step = 0;
	CurrentExerciseEvaluation.Time = UGameplayStatics::GetTimeSeconds(GetWorld());
	CurrentExerciseEvaluation.repeats = 0; 
	CurrentExerciseEvaluation.win = true;
}

void UEvaluationSubsystem::FinishExerciseEvaluation(bool &ExerciesesFinished)
{
	CurrentExerciseEvaluation.Time = UGameplayStatics::GetTimeSeconds(GetWorld()) - CurrentExerciseEvaluation.Time;
	CurrentExerciseEvaluation.Step = SessionResults.ActivityExercises.Num();
	SessionResults.ActivityExercises.Add(CurrentExerciseEvaluation);
	NextExercise(ExerciesesFinished);
}

void UEvaluationSubsystem::AddExercisesToActivity(UExerciseDataAsset* ExerciseData)
{	
	Questions.Append(ExerciseData->Questions);
	SelectedExercises.AddUnique(ExerciseData);
}

void UEvaluationSubsystem::StartActivity()
{
	CurrentExercise = 0;
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, SelectedExercises[CurrentExercise]->ExerciseLevel);	

}

void UEvaluationSubsystem::NextExercise(bool &ActivityFinished)
{
	CurrentExercise++;
	ActivityFinished = !SelectedExercises.IsValidIndex(CurrentExercise);
	if (ActivityFinished) return;			
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, SelectedExercises[CurrentExercise]->ExerciseLevel);	
}

UExerciseDataAsset* UEvaluationSubsystem::GetCurrentExercise()
{
	if (SelectedExercises.IsValidIndex(CurrentExercise))
	{
		return SelectedExercises[CurrentExercise];	
	}
	return nullptr;
}

void UEvaluationSubsystem::FinishActivity()
{
	UGameplayStatics::OpenLevel(GWorld, EntryLevelName, false);
}


