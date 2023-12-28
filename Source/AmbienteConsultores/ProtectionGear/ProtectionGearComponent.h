// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProtectionGearComponent.generated.h"


class UProtectionStrategy;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class AMBIENTECONSULTORES_API UProtectionGearComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UProtectionGearComponent();

	UPROPERTY(BlueprintReadWrite)
	UProtectionStrategy* ProtectionStrategy;

	UPROPERTY(BlueprintReadWrite)
	bool IsNecessary;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PutOn();
};
