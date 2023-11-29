// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "ModuleDataAsset.generated.h"

class UExerciseDataAsset;

USTRUCT(BlueprintType)
struct FModuleData
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag Module;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString ModuleID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UExerciseDataAsset*> Exercises;	
};


UCLASS(BlueprintType)
class AMBIENTECONSULTORES_API UModuleDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FModuleData Module;	
};
