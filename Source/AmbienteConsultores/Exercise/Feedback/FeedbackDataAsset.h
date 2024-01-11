// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FeedbackDataAsset.generated.h"

class UBaseStepFeedback;

UCLASS(BlueprintType)
class AMBIENTECONSULTORES_API UFeedbackDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:	
	UPROPERTY(BlueprintReadOnly, Instanced, EditInstanceOnly)
	TMap<FString, const UBaseStepFeedback*> InternalStepFeedback;

	UPROPERTY(BlueprintReadOnly, Instanced, EditInstanceOnly)
	const UBaseStepFeedback* StepStartFeedback;
	
	UPROPERTY(BlueprintReadOnly, Instanced, EditInstanceOnly)
	const UBaseStepFeedback* StepFinishedSuccessFeedback;

	UPROPERTY(BlueprintReadOnly, Instanced, EditInstanceOnly)
	const UBaseStepFeedback* StepFinishedFailFeedback;

	UPROPERTY(BlueprintReadOnly, Instanced, EditInstanceOnly)
	const UBaseStepFeedback* StepFinishedDelayedFailFeedback;
	
};
