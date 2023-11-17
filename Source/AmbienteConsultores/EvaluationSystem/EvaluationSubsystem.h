// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EvaluationSubsystem.generated.h"

UENUM(BlueprintType)
enum class EModule : uint8 
{
	Modulo1 UMETA(DisplayName="Manos"),
	Modulo2 UMETA(DisplayName="Eléctrico"),
	Modulo3 UMETA(DisplayName="Minas"),
	Modulo4 UMETA(DisplayName="Carros"),
	Modulo5 UMETA(DisplayName="Aviones"),
	Modulo6 UMETA(DisplayName="Industria"),
	Modulo7 UMETA(DisplayName="Metalurgia"),
};

UENUM(BlueprintType)
enum class EExercise : uint8 
{
	Exercise1,
	Exercise2,
	Exercise3
};

UENUM(BlueprintType)
enum EMichiStates
{
	X,
	O,
	CLEAR
};

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

	UPROPERTY()
	EModule Module;
	
	UPROPERTY()
	TArray<EExercise> Exercises;
	
};
