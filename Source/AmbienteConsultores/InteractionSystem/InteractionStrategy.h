

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractionStrategy.generated.h"

class IInteractionStrategy;

DECLARE_DYNAMIC_DELEGATE(FOnInteractionGoalAchieved);

UINTERFACE(BlueprintType) class UInteractionStrategy : public UInterface { GENERATED_BODY() };

class AMBIENTECONSULTORES_API IInteractionStrategy
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void IStartInteraction(AActor *Interactor, AActor *Interactable);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void IEndInteraction(AActor *Interactor, AActor *Interactable);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void IBindToOnInteractionGoalAchieved(const FOnInteractionGoalAchieved& Event);
};
