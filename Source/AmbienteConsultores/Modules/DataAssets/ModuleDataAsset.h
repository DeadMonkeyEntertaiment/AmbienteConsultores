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
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	FGameplayTag ModuleTag;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	FString ModuleID;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	TSoftObjectPtr<UWorld> ModuleLevel;	

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	UTexture2D* Image;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	TArray<UExerciseDataAsset*> Exercises;	
};
