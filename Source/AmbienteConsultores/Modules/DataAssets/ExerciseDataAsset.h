// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ExerciseDataAsset.generated.h"

class ABaseHoldableGrabbable;
class UEvaluationDataAsset;
class UImage;
enum class EModule : uint8;
enum class EExercise : uint8;

UENUM(BlueprintType)
enum class EExercise : uint8 
{
	Exercise1 UMETA(DisplayName="Cuidado de manos"),
	Exercise2 UMETA(DisplayName="Control de oleadas"),
	Exercise3 UMETA(DisplayName="Diveos"),	
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EExercise Exercise;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UWorld> ExerciseLevel;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FQuestion> Questions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FInstructorDialog> InstructorDialogs;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<ABaseHoldableGrabbable>> ProtectionGear;

};
