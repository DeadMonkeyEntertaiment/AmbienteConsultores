// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UtilityBlueprintFunctionLibrary.generated.h"

class UBaseStepFeedback;
UENUM(BlueprintType)
enum EValidationPins
{
	Valid = 0,
	NotValid = 1
};

/**
 * 
 */
UCLASS()
class UUtilityBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, meta=(ComponentClass = "ActorComponent", DeterminesOutputType = "ComponentClass", ExpandEnumAsExecs = "Outcome"))
	static UActorComponent* GetValidatedComponentByClass(AActor* Target, TSubclassOf<UActorComponent> ComponentClass,
	                                                     TEnumAsByte<EValidationPins>& Outcome);

	UFUNCTION(BlueprintCallable, meta=(ComponentClass = "ActorComponent", DeterminesOutputType = "ComponentsClass", ExpandEnumAsExecs = "Outcome"))
	static TArray<UActorComponent*> GetValidatedComponentsByClass(AActor* Target, const TSubclassOf<UActorComponent> ComponentClass,
													 TEnumAsByte<EValidationPins>& Outcome);

	UFUNCTION(BlueprintCallable, meta=(ComponentClass = "Feedback", DeterminesOutputType = "ComponentsClass", ExpandEnumAsExecs = "Outcome"))
	static UBaseStepFeedback* GetValidatedFeedback(TArray<UBaseStepFeedback*> Feedbacks, int index, TEnumAsByte<EValidationPins>& Outcome);
};