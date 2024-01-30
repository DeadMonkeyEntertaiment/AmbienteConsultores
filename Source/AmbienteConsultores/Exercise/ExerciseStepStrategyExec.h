// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ExerciseBoxCollision.h"
#include "AmbienteConsultores/InteractionSystem/BaseInteractable.h"
#include "AmbienteConsultores/InteractionSystem/InteractableComponent.h"
#include "AmbienteConsultores/Utils/BaseTickableObject.h"
#include "ExerciseStepStrategyExec.generated.h"

class APlayerStart;
class AExerciseBoxCollision;
class UFeedbackDataAsset;
class UFailStrategy;

USTRUCT(BlueprintType)
struct FStepsToDisable
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTagContainer StepsToDisable;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool PropagateToInteractables;
	
};

USTRUCT(BlueprintType)
struct FStepsToDisable2 
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTagContainer StepsToDisable;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool PropagateToInteractables;
	
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnStepStarted, FGameplayTag, StepTag, FStepsToDisable, StepsToDisable, const UBaseStepFeedback*, SuccessFeedback, const UBaseStepFeedback*, FailFeedback,  const UBaseStepFeedback*, DelayedFailFeedback);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnStepFinished, FGameplayTag, StepTag, FStepsToDisable, StepsToDisable, bool, Success, const UBaseStepFeedback*, Feedback, const UBaseStepFeedback*, DelayedFailFeedback);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStepInternalFeedback, UBaseStepFeedback*, Feedback);


UCLASS(Blueprintable, BlueprintType, Abstract)
class AMBIENTECONSULTORES_API UExerciseStepStrategyExec : public UBaseTickableObject
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Setup")
	void SetupStep(APawn* playerPawn, UExerciseStepStrategyDef* Def);
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnStepStarted OnStepStart;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnStepFinished OnStepFinish;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="Definition")
	FGameplayTag StepTag;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="FlowControl")
	bool LastStepWaitForOkGesture;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="FlowControl")
	bool Autostart;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Sublevel")
	bool ChangeSublevel;

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
	
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="Steps To Desable")
	bool AutoDisableAfterFinished;
	
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="Steps To Desable")
	bool AutoDisableInteractablesAfterFinished;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Steps To Desable")
	FStepsToDisable StepsToDisableOnStart;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Steps To Desable")
	FStepsToDisable StepsToDisableOnFinish;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetStepEnable(bool Enable, bool PropagateToInteracts);	
	
protected:
	UPROPERTY(BlueprintReadOnly)
	bool bStepEnable = true;

	UPROPERTY(BlueprintReadOnly)
	APawn* PlayerPawn;

	UPROPERTY()
	FOnInteractionStarted InteractionStartedActivationReqHandler;
	
	UPROPERTY()	
	FOnInteractionGoalAchieved InteractionGoalActivationReqHandler;
	
	UPROPERTY()
	FOnInteractionFinished ForceFinishInteractionActivationReqHandler;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnStepInternalFeedback OnStepInternalFeedback;
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Interaction")
	void OnInteractableInteractionStarted(AActor* Interactor, AActor* Interactable);
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Interaction")
	void OnInteractableInteractionGoalAchieved(AActor* Interactor, AActor* Interactable);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Interaction")
	void OnInteractableInteractionFinished(AActor* Interactor, AActor* Interactable);
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Interaction")
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Utils")
	void CallOnStepStart();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Utils")
	void AutostartStep();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Utils")
	void CallOnStepFinished(bool Success);
};
