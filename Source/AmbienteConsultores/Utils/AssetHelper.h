// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AssetHelper.generated.h"

/**
 * 
 */
UCLASS()
class UAssetHelper : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static TArray<UObject*> LoadAssetsFromClass(UClass* Class);
};