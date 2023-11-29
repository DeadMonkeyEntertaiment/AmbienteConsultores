// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MissionNode.h"
#include "GenericGraph.h"
#include "MissionGraph.generated.h"

/**
 * 
 */
UCLASS()
class UMissionGraph : public UGenericGraph
{
	GENERATED_BODY()

	UMissionGraph();

public:
	UFUNCTION(BlueprintCallable) TArray<UMissionNode*> GetOrderedList();

	UFUNCTION(BlueprintCallable) FString ToString();
};
