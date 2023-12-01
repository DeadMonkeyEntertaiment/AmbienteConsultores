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
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnStepStarted, FGameplayTag, StepTag, UStepFeedback*, SuccessFeedback, UStepFeedback*, FailFeedback);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnStepFinished, FGameplayTag, StepTag, FGameplayTagContainer, StepsToDisable, bool, Success, UStepFeedback*, Feedback);



UCLASS(Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew, Abstract)
class AMBIENTECONSULTORES_API UExerciseStepStrategy : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FOnInteractionStarted InteractionStartedActivationReqHandler;
	
	UPROPERTY()	
	FOnInteractionGoalAchieved InteractionGoalActivationReqHandler;
	
	UPROPERTY()
	FOnInteractionFinished ForceFinishInteractionActivationReqHandler;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Setup")
	void SetupStepBindings();

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnStepStarted OnStepStart;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnStepFinished OnStepFinish;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTag StepTag;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTagContainer StepsToDisable;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TSoftObjectPtr<ABaseInteractable>> InteractActors;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TSoftObjectPtr<AExerciseBoxCollision>> BoxColliders;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStepFeedback* SuccessFeedback;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStepFeedback* FailFeedback;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetStepEnable(bool Enable);	
	
protected:	
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
	void CallOnStepFinished(bool Success);

	UPROPERTY(BlueprintReadOnly)
		bool bStepEnable = true;

};
