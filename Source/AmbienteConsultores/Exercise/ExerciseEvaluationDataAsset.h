// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AmbienteConsultores/Engine/DataDriven/DataContainer.h"
#include "Engine/DataAsset.h"
#include "ExerciseEvaluationDataAsset.generated.h"

class UExerciseStepStrategy;
class UExerciseStepDataAsset;
class UExerciseDataAsset;

UCLASS(BlueprintType)
class AMBIENTECONSULTORES_API UExerciseEvaluationDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TArray<TObjectPtr<UExerciseStepStrategy>> SuccessExerciseSteps;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TArray<TObjectPtr<UExerciseStepStrategy>> FailExerciseSteps;
	

	
};
