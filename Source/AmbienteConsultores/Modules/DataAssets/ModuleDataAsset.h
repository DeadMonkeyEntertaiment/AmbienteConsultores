// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "ModuleDataAsset.generated.h"

class UExerciseDataAsset;

UCLASS(BlueprintType)
class AMBIENTECONSULTORES_API UModuleDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag ModuleTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString ModuleID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UWorld> ModuleLevel;	

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UExerciseDataAsset*> Exercises;	
};
