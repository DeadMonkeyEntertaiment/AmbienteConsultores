// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "ExerciseEvaluationDataAsset.generated.h"

class UExerciseDataAsset;

UCLASS(BlueprintType)
class AMBIENTECONSULTORES_API UExerciseEvaluationDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSoftObjectPtr<ABaseInteractable>> InteractActors;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSoftObjectPtr<ABaseInteractable>> InteractionGoalActors;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSoftObjectPtr<AExerciseBoxCollision>> BoxColliders;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTagContainer StepsTagsContainer;
	

	
};
