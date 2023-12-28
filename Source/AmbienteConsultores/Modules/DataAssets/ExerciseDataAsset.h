// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AmbienteConsultores/Exercise/ExerciseEvaluationDataAsset.h"
#include "ExerciseDataAsset.generated.h"

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
	bool Necessary = true;
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
	TSoftObjectPtr<UWorld> ExerciseActorsSublevel;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UExerciseEvaluationDataAsset* ExerciseEvaluationDataAsset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool HasPointer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool HasMovement;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool FemaleInstructor = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FQuestion> Questions;	

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FProtectionGear> ProtectionGear;
};
