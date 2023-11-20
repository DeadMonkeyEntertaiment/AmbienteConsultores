// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ExerciseDataAsset.generated.h"

class UEvaluationDataAsset;
class UImage;
enum class EModule : uint8;
enum class EExercise : uint8;

UENUM(BlueprintType)
enum class EExercise : uint8 
{
	Exercise1,
	Exercise2,
	Exercise3
};

USTRUCT(BlueprintType)
struct FInstructorDialog
{
	GENERATED_BODY()	

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundBase* Audio;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimationAsset* Animation;

	UPROPERTY(meta=(MultiLine), EditAnywhere, BlueprintReadOnly)
	TArray<FText> Texts;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<float> AudioToTextSegmentationTimes;	
};

USTRUCT(BlueprintType)
struct FQuestion
{
	GENERATED_BODY()
	
	UPROPERTY(meta=(MultiLine), EditAnywhere, BlueprintReadOnly)
	FText Question;	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FText> Answers;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 CorrectAnswer;	
};

UCLASS(BlueprintType)
class AMBIENTECONSULTORES_API UExerciseDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EExercise Exercise;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UWorld> ExperienceLevel;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FQuestion> Questions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FInstructorDialog> InstructorDialogs;

};
