// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "ModuleDataAsset.generated.h"

class UExerciseDataAsset;
class AInstructorLocation;
class ABaseProtectionGear;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator SpawnRotation = {0,0,0};
};

USTRUCT(BlueprintType)
struct FInstructorFeedback
{
	GENERATED_BODY()	

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundBase* Audio;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* AnimationMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<AInstructorLocation> InstructorLocation;

	UPROPERTY(meta=(MultiLine), EditAnywhere, BlueprintReadOnly)
	TArray<FText> Texts;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<float> AudioToTextSegmentationTimes;	
};


UCLASS(BlueprintType)
class AMBIENTECONSULTORES_API UModuleDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	FGameplayTag ModuleTag;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	FString ModuleID;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	TSoftObjectPtr<UWorld> ModuleLevel;	

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	UTexture2D* Image;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	UExerciseDataAsset* EPPExercise;	
	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	TArray<UExerciseDataAsset*> Exercises;	
};
