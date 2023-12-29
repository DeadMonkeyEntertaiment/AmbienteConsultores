// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "ExerciseDataAsset.generated.h"

class UExerciseStepStrategy;
class APlayerStart;
class AInstructorLocation;
class ABaseProtectionGear;
class ABaseHoldableGrabbable;
class UEvaluationDataAsset;
class UImage;

USTRUCT(BlueprintType)
struct FQuestion
{
	GENERATED_BODY()
	
	UPROPERTY(meta=(MultiLine), EditAnywhere, BlueprintReadOnly)
	FText Question;	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FText> Answers
	{
		FText::FromString("Verdadero"), FText::FromString("Falso")
	};

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 CorrectAnswer;	
};

USTRUCT(BlueprintType)
struct FProtectionGear
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ABaseProtectionGear> ProtectionGearClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int StackNumber;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsNecessary = true;
};

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
class AMBIENTECONSULTORES_API UExerciseDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag ExerciseTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Sublevels")
	TArray<TSoftObjectPtr<UWorld>> ExerciseSublevels;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Sublevels")
	TSoftObjectPtr<UWorld> ExerciseActorsSublevel;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FQuestion> Questions;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="EPP")
	TArray<FProtectionGear> ProtectionGear;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="EPP")
	FInstructorFeedback EPPSTartDialog;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="EPP")
	FInstructorFeedback EPPSuccessDialog;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="EPP")
	FInstructorFeedback EPPFailedDialog;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Player")
	bool HasPointer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Player")
	bool HasMovement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Player")
	TSoftObjectPtr<APlayerStart> PlayerStart;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Instructor")
	bool FemaleInstructor = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Instructor")
	FInstructorFeedback StartDialog;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Instructor")
	FInstructorFeedback EndDialog;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category="Steps")
	TArray<UExerciseStepStrategy*> SuccessExerciseSteps;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category="Steps")
	TArray<UExerciseStepStrategy*> FailExerciseSteps;
	
};
