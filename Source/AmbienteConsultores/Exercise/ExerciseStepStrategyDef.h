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

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="FlowControl")
	bool Autostart;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="FlowControl")
	bool InitializeEnable = true;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="FlowControl")
	bool PropagateToInteractables = true;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="FlowControl")
	bool AutoDisableAfterFinished;
	
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="FlowControl")
	bool AutoDisableInteractablesAfterFinished;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Sublevel")
	bool ChangeSublevel;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Sublevel")
	bool UnloadPreviousSublevel = true;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Sublevel")
	TSoftObjectPtr<UWorld> StepSublevel;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Sublevel")
	TSoftObjectPtr<APlayerStart> SublevelPlayerStart;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Sublevel")
	bool SetStepAsNewReset;
	
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="Interactables & Colliders")
	TArray<TSoftObjectPtr<ABaseInteractable>> InteractActors;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="Interactables & Colliders")
	TArray<TSoftObjectPtr<AExerciseBoxCollision>> BoxColliders;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="Interactables & Colliders")
	TMap<FString, TSoftObjectPtr<AActor>> AdditionalActors;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="Feedback")
	UFeedbackDataAsset* FeedbackDA;	
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Steps Control")
	FStepsToControl StepsToDisableOnStart;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Steps Control")
	FStepsToControl StepsToDisableOnFinish;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Steps Control")
	FStepsToControl StepsToEnableOnFinish;
};
