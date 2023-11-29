// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericGraphNode.h"
#include "MissionNode.generated.h"

/**
 * 
 */
UCLASS(HideCategories=(GenericGraphNode, GenericGraphNode_Editor))
class UMissionNode : public UGenericGraphNode
{
	GENERATED_BODY()

public:
	UMissionNode();

#if WITH_EDITOR
	virtual FText GetNodeTitle() const override;
#endif
};
