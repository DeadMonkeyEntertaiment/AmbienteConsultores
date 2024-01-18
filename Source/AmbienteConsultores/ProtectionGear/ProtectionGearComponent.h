// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ProtectionStrategy.h"
#include "Components/ActorComponent.h"
#include "ProtectionGearComponent.generated.h"



class UInteractionStrategy;
class UProtectionStrategy;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEPPRemoved, AActor*, ProtectionGear);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class AMBIENTECONSULTORES_API UProtectionGearComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UProtectionGearComponent();	

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag EPPTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int StackNumber;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform SpawnedLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnScale = 1;

	UPROPERTY(BlueprintReadWrite)
	bool IsNecessary;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Equip(AActor* player);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Remove();

	UFUNCTION(BlueprintCallable)
	void Setup(bool Necessary, int StackNum, FTransform Location);

	UFUNCTION(BlueprintCallable)
	void BindToOnPutOn(const FOnPutOnInternal& event);

	
protected:
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category="ProtectionGear")
	UProtectionStrategy* ProtectionStrategyObject;

	UPROPERTY(EditAnywhere, BlueprintAssignable, Category="ProtectionGear")
	FOnEPPRemoved OnEppRemoved;	
};
