// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EvaluationSubsystem.generated.h"

struct FQuestion;
enum class EExercise : uint8;
enum class EModule : uint8;


USTRUCT(BlueprintType)
struct FExerciseEvaluation
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EExercise Exercise; //description
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	double Time;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 repeats;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool win;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Step;	
};

USTRUCT(BlueprintType)
struct FSessionResults
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EModule SelectedModule;; //CourseId

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FExerciseEvaluation> ActivityExercises; //ActivitySteps
};

UCLASS(Blueprintable)
class AMBIENTECONSULTORES_API UEvaluationSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:	

	//Questionnaire
	UPROPERTY(BlueprintReadOnly)	
	TArray<FQuestion> Questions;		
	
	UFUNCTION(BlueprintCallable)
	void StoreQuestionnaireScore(const int32 EvaluationScore);
	
	UFUNCTION(BlueprintCallable)
	void AddFailedAttempt();
	
	UFUNCTION(BlueprintCallable)
	void AddSuccessfulAttempt();

	UFUNCTION(BlueprintCallable)
	void ResetQuestionnaire();

	UFUNCTION(BlueprintCallable)
	void SetSelectedModule(const EModule Module);
	
	UFUNCTION(BlueprintCallable)
	void StartExerciseEvaluation(const EExercise Exercise);

	UFUNCTION(BlueprintCallable)
	void FinishExerciseEvaluation();

	//This should be privatre, i put here only for easy testing 
	UPROPERTY(BlueprintReadWrite)
	FExerciseEvaluation CurrentExerciseEvaluation;

	UPROPERTY(BlueprintReadOnly)
	FSessionResults SessionResults;

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
	int32 UserID;
	
	UPROPERTY()	
	int32 QuestionnaireScore;
	

	UPROPERTY()
	TArray<UExerciseDataAsset*> SelectedExercises;

	UPROPERTY()
	int32 CurrentExercise;
	
	//UPROPERTY()
	//TArray<EExercise> SelectedExercises;

	//UPROPERTY()
	//TArray<FExerciseEvaluation> ActivityExercises;	
};
