// Fill out your copyright notice in the Description page of Project Settings.


#include "EvaluationSubsystem.h"

#include "EvaluationDataAsset.h"
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

void UEvaluationSubsystem::StartEvaluation(const int32 userID)
{
	UserID = userID;
	SuccessfulAttempts = 0;
	FailedAttempts = 0;
	EvaluationScore =0;
}

void UEvaluationSubsystem::AddEvaluationDataAssets(UEvaluationDataAsset* EvaluationDataAsset)
{
	EvaluationDataAssets.AddUnique(EvaluationDataAsset);
}


