// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ExerciseBoxCollision.h"
#include "ExerciseStepStrategyExec.h"
#include "AmbienteConsultores/InteractionSystem/BaseInteractable.h"
#include "ExerciseStepStrategyDef.generated.h"

class UFeedbackDataAsset;
class UFailStrategy;

UCLASS(Blueprintable, BlueprintType, EditInlineNew)
class AMBIENTECONSULTORES_API UExerciseStepStrategyDef : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Definition")
	TSubclassOf<UExerciseStepStrategyExec> StepStrategyClass;
	
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="Definition")
	FGameplayTag StepTag;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Autostart")
	bool Autostart;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="Interactables & Colliders")
	TArray<TSoftObjectPtr<ABaseInteractable>> InteractActors;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="Interactables & Colliders")
	TArray<TSoftObjectPtr<AExerciseBoxCollision>> BoxColliders;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="Interactables & Colliders")
	TMap<FString, TSoftObjectPtr<AExerciseBoxCollision>> AdditionalActors;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="Feedback")
	UFeedbackDataAsset* FeedbackDA;
	
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="Steps To Desable")
	bool AutoDisableAfterFinished;
	
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="Steps To Desable")
	bool AutoDisableInteractablesAfterFinished;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Steps To Desable")
	FStepsToDisable StepsToDisableOnStart;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Steps To Desable")
	FStepsToDisable StepsToDisableOnFinish;
};
