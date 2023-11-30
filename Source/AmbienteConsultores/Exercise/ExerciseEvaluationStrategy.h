#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "ExerciseEvaluationStrategy.generated.h"

struct FGameplayTagContainer;
class AExerciseBoxCollision;
class UBoxComponent;
class ABaseInteractable;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttemptFinished, bool, Succes);

UCLASS(Blueprintable, BlueprintType, Abstract)
class AMBIENTECONSULTORES_API UExerciseEvaluationStrategy : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintCallable, BlueprintAssignable);
	FOnAttemptFinished OnAttemptFinished;

protected:
	//UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn="true"))
	//TSubclassOf<Exer> InteractActors;
	
	/*
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetupEvaluationBindings();
	
protected:

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn="true"))
	TArray<TSoftObjectPtr<ABaseInteractable>> InteractActors;
	
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn="true"))
	TArray<TSoftObjectPtr<ABaseInteractable>> InteractActors;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn="true"))
	TArray<TSoftObjectPtr<ABaseInteractable>> InteractionGoalActors;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn="true"))
	TArray<TSoftObjectPtr<AExerciseBoxCollision>> BoxColliders;

	UPROPERTY(BlueprintReadWrite)
	FGameplayTagContainer StepsTagsContainer;

	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnInteractionStarted(AActor* Interactor, AActor* Interactable);
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnInteractionGoalAchieved(AActor* Interactor, AActor* Interactable);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnInteractionFinished(AActor* Interactor, AActor* Interactable);
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	*/
};
