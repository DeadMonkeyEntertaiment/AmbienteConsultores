// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MissionRewardBase.generated.h"

/**
 * 
 */
UCLASS(EditInlineNew, BlueprintType, CollapseCategories, Abstract)
class UMissionRewardBase : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION()
	virtual void Claim(AActor* PlayerCharacter);
};
