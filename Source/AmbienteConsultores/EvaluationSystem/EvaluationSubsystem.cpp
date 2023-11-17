// Fill out your copyright notice in the Description page of Project Settings.


#include "EvaluationSubsystem.h"
#include "AmbienteConsultores/Modules/DataAssets/ExerciseDataAsset.h"
#include "Kismet/GameplayStatics.h"

void UEvaluationSubsystem::StoreEvaluationScore(const int32 evaluationScore)
{
	EvaluationScore = evaluationScore;
}

void UEvaluationSubsystem::AddFailedAttempt()
{
	FailedAttempts++;
}

void UEvaluationSubsystem::AddSuccessfulAttempt()
{
	SuccessfulAttempts++;
}

void UEvaluationSubsystem::ResetEvaluation()
{	
	SuccessfulAttempts = 0;
	FailedAttempts = 0;
	EvaluationScore =0;
	Questions.Empty();
}

void UEvaluationSubsystem::AddQuestions(TArray<FQuestion> questions)
{
	Questions.Append(questions);
}

void UEvaluationSubsystem::SetSelectedModule(const EModule Module)
{
	SelectedModule = Module;
}


