// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ExerciseBoxCollision.h"
#include "AmbienteConsultores/InteractionSystem/BaseInteractable.h"
#include "AmbienteConsultores/InteractionSystem/InteractableComponent.h"
#include "ExerciseStepStrategy.generated.h"

class UStepFeedback;
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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnStepStarted, FGameplayTag, StepTag, FStepsToDisable, StepsToDisable, UStepFeedback*, SuccessFeedback, UStepFeedback*, FailFeedback,  UStepFeedback*, DelayedFailFeedback);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnStepFinished, FGameplayTag, StepTag, FStepsToDisable, StepsToDisable, bool, Success, UStepFeedback*, Feedback, UStepFeedback*, DelayedFailFeedback);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStepInternalFeedback, UStepFeedback*, Feedback);


UCLASS(Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew, Abstract)
class AMBIENTECONSULTORES_API UExerciseStepStrategy : public UObject
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Setup")
	void SetupStepBindings();

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnStepStarted OnStepStart;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnStepFinished OnStepFinish;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Step Tag")
	FGameplayTag StepTag;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Steps To Desable")
	FStepsToDisable StepsToDisableOnStart;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Steps To Desable")
	FStepsToDisable StepsToDisableOnFinish;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Interactors & Colliders")
	TArray<TSoftObjectPtr<ABaseInteractable>> InteractActors;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Interactors & Colliders")
	TArray<TSoftObjectPtr<AExerciseBoxCollision>> BoxColliders;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Feedback")
	TArray<UStepFeedback*> StepInternalFeedbacks;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Feedback")
	UStepFeedback* SuccessFeedback;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Feedback")
	UStepFeedback* InstantFailFeedback;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Feedback")
	UStepFeedback* DelayedFailFeedback;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetStepEnable(bool Enable, bool PropagateToInteracts);	
	
protected:
	UPROPERTY(BlueprintReadOnly)
	bool bStepEnable = true;

	UPROPERTY()
	FOnInteractionStarted InteractionStartedActivationReqHandler;
	
	UPROPERTY()	
	FOnInteractionGoalAchieved InteractionGoalActivationReqHandler;
	
	UPROPERTY()
	FOnInteractionFinished ForceFinishInteractionActivationReqHandler;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnStepInternalFeedback OnStepInternalFeedback;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction")
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
	void CallOnStepFinished(bool Success);
};
