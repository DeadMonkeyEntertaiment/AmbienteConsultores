// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStepFeedback.h"
#include "UObject/Object.h"
#include "HighlightFeedback.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew, Abstract)
class AMBIENTECONSULTORES_API UHighlightFeedback : public UBaseStepFeedback
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn="true"))
	TArray<TSoftObjectPtr<AActor>> ActorsToHighlight;
};
