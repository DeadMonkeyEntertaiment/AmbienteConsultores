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
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStepStarted, FGameplayTag, StepTag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnStepFinished, FGameplayTag, StepTag, FGameplayTagContainer, StepsToDisable, bool, Success);



UCLASS(Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew, Abstract)
class AMBIENTECONSULTORES_API UExerciseStepStrategy : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetupStepBindings();

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnStepStarted OnStepStart;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnStepFinished OnStepFinish;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn="true"))
	FGameplayTag StepTag;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn="true"))
	FGameplayTagContainer StepsToDisable;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn="true"))
	TArray<TSoftObjectPtr<ABaseInteractable>> InteractActors;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn="true"))
	TArray<TSoftObjectPtr<AExerciseBoxCollision>> BoxColliders;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn="true"))
	UStepFeedback* SuccessFeedback;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn="true"))
	UStepFeedback* FailFeedback;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetStepEnable(bool Enable);
	
protected:	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnInteractionStarted(AActor* Interactor, AActor* Interactable);
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnInteractionGoalAchieved(AActor* Interactor, AActor* Interactable);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnInteractionFinished(AActor* Interactor, AActor* Interactable);
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void CallOnStepStart();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void CallOnStepFinished(bool Success);

	UPROPERTY(BlueprintReadOnly)
	bool IsStepEnable = true;

};
