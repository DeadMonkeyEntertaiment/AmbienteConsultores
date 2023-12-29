// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProtectionGearComponent.generated.h"

class UInteractionStrategy;
class UProtectionStrategy;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class AMBIENTECONSULTORES_API UProtectionGearComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UProtectionGearComponent();	
	
	UPROPERTY(BlueprintReadWrite)
	bool IsNecessary;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PutOn(AActor* player);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Remove();

protected:
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category="ProtectionGear")
	UProtectionStrategy* ProtectionStrategyObject;
};
