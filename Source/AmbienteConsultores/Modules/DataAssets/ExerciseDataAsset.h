// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AmbienteConsultores/Exercise/ExerciseEvaluationDataAsset.h"
#include "AmbienteConsultores/InteractionSystem/InteractableInterface.h"
#include "ExerciseDataAsset.generated.h"

class AInstructorLocation;
class ABaseInteractable;
class ABaseHoldableGrabbable;
class UEvaluationDataAsset;
class UImage;

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
	FGameplayTag ExerciseTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSoftObjectPtr<UWorld>> ExerciseSublevels;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UExerciseEvaluationDataAsset* ExerciseEvaluationDataAsset;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FQuestion> Questions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FInstructorFeedback InitialDialog;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FInstructorFeedback FinalDialog;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<ABaseInteractable>> ProtectionGear;
};
