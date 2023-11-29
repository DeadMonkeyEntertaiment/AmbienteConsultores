// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataContainer.h"
#include "UObject/Object.h"
#include "DataDrivenHelper.generated.h"

/**
 * 
 */
UCLASS()
class UDataDrivenHelper : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static UDataContainer* GetDataContainer(AActor* Target);
};
