// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EvaluationSubsystem.generated.h"

struct FQuestion;
enum class EExercise : uint8;
enum class EModule : uint8;

UCLASS()
class AMBIENTECONSULTORES_API UEvaluationSubsystem : public UGameInstanceSubsystem 
{
	GENERATED_BODY()
	
public:	

	UFUNCTION(BlueprintCallable)
	void StoreEvaluationScore(const int32 EvaluationScore);
	
	UFUNCTION(BlueprintCallable)
	void AddFailedAttempt();
	
	UFUNCTION(BlueprintCallable)
	void AddSuccessfulAttempt();

	UFUNCTION(BlueprintCallable)
	void ResetEvaluation();

	UFUNCTION(BlueprintCallable)
	void AddQuestions(TArray<FQuestion> questions);	
	
	UPROPERTY(BlueprintReadOnly)	
	TArray<FQuestion> Questions;		

	UFUNCTION(BlueprintCallable)
	void SetSelectedModule(const EModule Module);
	
private:
	UPROPERTY()
	int32 FailedAttempts;
	
	UPROPERTY()	
	int32 SuccessfulAttempts;
	
	UPROPERTY()	
	int32 EvaluationScore;
	
	UPROPERTY()
	int32 UserID;

	UPROPERTY()
	EModule SelectedModule;
	
	UPROPERTY()
	TArray<EExercise> SelectedExercises;
	
};
