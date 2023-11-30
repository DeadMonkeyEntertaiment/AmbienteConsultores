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
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetupEvaluationBindings();
	
protected:
	
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn="true"))
	TArray<ABaseInteractable*> InteractActors;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn="true"))
	TArray<ABaseInteractable*> InteractionGoalActors;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn="true"))
	TArray<AExerciseBoxCollision*> BoxColliders;

	UPROPERTY(BlueprintReadWrite)
	FGameplayTagContainer StepsTagsContainer;

	
};
