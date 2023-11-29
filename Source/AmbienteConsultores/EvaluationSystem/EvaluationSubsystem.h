// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
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
	FGameplayTag Exercise; //description
	
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
	FGameplayTag SelectedModule;; //CourseId

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FExerciseEvaluation> ActivityExercises; //ActivitySteps
};

UCLASS(Blueprintable)
class AMBIENTECONSULTORES_API UEvaluationSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	
	//Questionnaire
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<FQuestion> GetQuestions();
	
	UFUNCTION(BlueprintCallable)
	void StoreQuestionnaireScore(const int32 EvaluationScore);

	UFUNCTION(BlueprintCallable)
	void ResetQuestionnaire();

	//Exercise
	UFUNCTION(BlueprintCallable)
	void AddFailedAttempt();
	
	UFUNCTION(BlueprintCallable)
	void AddSuccessfulAttempt();
	
	UFUNCTION(BlueprintCallable)
	UExerciseDataAsset* GetCurrentExercise();

	//Evaluation
	UFUNCTION(BlueprintCallable)
	void SetSelectedModule(const FGameplayTag Module);

	UFUNCTION(BlueprintCallable)
	void AddExercisesToActivity(UExerciseDataAsset* ExerciseData);
	
	UFUNCTION(BlueprintCallable)
	void StartActivity();
	
	UFUNCTION(BlueprintCallable)
	void StartExerciseEvaluation();	
	
	UFUNCTION(BlueprintCallable)
	void FinishExerciseEvaluation(bool &ActivityFinished);

	UFUNCTION(BlueprintCallable)
	void NextExercise(bool &ActivityFinished);	

	UFUNCTION(BlueprintCallable)
	void FinishActivity();

	//This should be privatre, i put here only for easy testing 
	UPROPERTY(BlueprintReadWrite)
	FExerciseEvaluation CurrentExerciseEvaluation;
	//This should be privatre, i put here only for easy testing 
	UPROPERTY(BlueprintReadOnly)
	FSessionResults SessionResults;
	
private:	
	UPROPERTY()
	int32 UserID;

	UPROPERTY()
	TArray<UExerciseDataAsset*> SelectedExercises;

	UPROPERTY()
	FGameplayTag SelectedModule;

	UPROPERTY()
	int32 CurrentExercise;

	UPROPERTY()	
	TArray<FQuestion> Questions;	
	
	UPROPERTY()	
	int32 QuestionnaireScore;

	UPROPERTY()
	FName EntryLevelName = "/Game/Maps/MAP_EntryLevel";	
};
