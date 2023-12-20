// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ExerciseEvaluationDataAsset.generated.h"

class APlayerStart;
class UExerciseStepStrategy;
class UExerciseStepDataAsset;
class UExerciseDataAsset;
class AInstructorLocation;

USTRUCT(BlueprintType)
struct FInstructorFeedback
{
	GENERATED_BODY()	

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundBase* Audio;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimationAsset* Animation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<AInstructorLocation> InstructorLocation;

	UPROPERTY(meta=(MultiLine), EditAnywhere, BlueprintReadOnly)
	TArray<FText> Texts;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<float> AudioToTextSegmentationTimes;	
};

UCLASS(BlueprintType)
class AMBIENTECONSULTORES_API UExerciseEvaluationDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FInstructorFeedback StartDialog;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FInstructorFeedback EndDialog;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TArray<const UExerciseStepStrategy*> SuccessExerciseSteps;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TArray<const UExerciseStepStrategy*> FailExerciseSteps;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<APlayerStart> PlayerStart;
};
