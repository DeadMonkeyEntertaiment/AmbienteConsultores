// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ModulesListDataAsset.generated.h"

class UModuleDataAsset;
enum class EModule : uint8;
enum class EExercise : uint8;

UCLASS(BlueprintType)
class AMBIENTECONSULTORES_API UModulesDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UModuleDataAsset*> Modules;	
};
