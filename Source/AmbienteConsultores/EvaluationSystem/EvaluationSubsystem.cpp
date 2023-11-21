// Fill out your copyright notice in the Description page of Project Settings.


#include "EvaluationSubsystem.h"
#include "AmbienteConsultores/Modules/DataAssets/ExerciseDataAsset.h"
#include "Kismet/GameplayStatics.h"

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

void UEvaluationSubsystem::AddQuestions(TArray<FQuestion> NewQuestions)
{
	Questions.Append(NewQuestions);
}

void UEvaluationSubsystem::SetSelectedModule(const EModule Module)
{
	SelectedModule = Module;
}

void UEvaluationSubsystem::StartExerciseEvaluation(const EExercise Exercise)
{
	CurrentExerciseEvaluation.Exercise = Exercise;
	CurrentExerciseEvaluation.Step = 0;
	CurrentExerciseEvaluation.Time = UGameplayStatics::GetTimeSeconds(GetWorld());
	CurrentExerciseEvaluation.repeats = 0; 
	CurrentExerciseEvaluation.win = true;
}

void UEvaluationSubsystem::FinishExerciseEvaluation()
{
	CurrentExerciseEvaluation.Time = UGameplayStatics::GetTimeSeconds(GetWorld()) - CurrentExerciseEvaluation.Time;
	CurrentExerciseEvaluation.Step = ActivityExercises.Num();
	ActivityExercises.Add(CurrentExerciseEvaluation);	
}


