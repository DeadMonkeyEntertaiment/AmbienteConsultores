// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ModuleDataAsset.generated.h"

class UExerciseDataAsset;
enum class EExercise : uint8;

UENUM(BlueprintType)
enum class EModule : uint8 
{
	Modulo1 UMETA(DisplayName="Manos"),
	Modulo2 UMETA(DisplayName="Eléctrico"),
	Modulo3 UMETA(DisplayName="Minas"),
	Modulo4 UMETA(DisplayName="Carros"),
	Modulo5 UMETA(DisplayName="Aviones"),
	Modulo6 UMETA(DisplayName="Industria"),
	Modulo7 UMETA(DisplayName="Metalurgia"),
};

USTRUCT(BlueprintType)
struct FModuleData
{
	GENERATED_BODY()
	UPROPERTY(meta=(MultiLine), EditAnywhere, BlueprintReadOnly)
	EModule Module;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UExerciseDataAsset*> Exercises;	
};


UCLASS(BlueprintType)
class AMBIENTECONSULTORES_API UModuleDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FModuleData Module;	
};
