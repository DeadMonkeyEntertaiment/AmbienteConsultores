// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EvaluationSubsystem.generated.h"

class UEvaluationDataAsset;
/**
 * 
 */
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
	void StartEvaluation(const int32 UserID);

	UFUNCTION(BlueprintCallable)
	void AddEvaluationDataAssets(UEvaluationDataAsset* EvaluationDataAsset);	

	UPROPERTY(BlueprintReadOnly)	
	TArray<UEvaluationDataAsset*> EvaluationDataAssets;
	
private:
	UPROPERTY()
	int32 FailedAttempts;
	
	UPROPERTY()	
	int32 SuccessfulAttempts;
	
	UPROPERTY()	
	int32 EvaluationScore;
	
	UPROPERTY()
	int32 UserID;	
};
