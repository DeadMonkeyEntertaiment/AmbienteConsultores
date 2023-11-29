// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "WorldRegistry.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRegistryEntryUpdated, TSubclassOf<AActor>, Category);

USTRUCT(BlueprintType)
struct FWorldRegistryEntry
{
	GENERATED_BODY()

	FWorldRegistryEntry(){}

	FWorldRegistryEntry(AActor* FirstActor)
	{
		RegisteredActors.Add(FirstActor);
	}

	UPROPERTY(BlueprintReadOnly)
	TArray<AActor*> RegisteredActors;
};


/**
 * 
 */
UCLASS()
class UWorldRegistry : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void Register(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	void Unregister(AActor* Actor);

	/**
	 * @brief 
	 * @param ActorClass 
	 * @return First actor of ActorClass found. Nullptr otherwise.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	AActor* FindActor(TSubclassOf<AActor> ActorClass, bool ExhaustiveSearch = false) const;

	/**
	 * @brief 
	 * @param ActorClass 
	 * @return All actors of class found. Empty array otherwise.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<AActor*> FindActors(TSubclassOf<AActor> ActorClass) const;

	/**
	 * @brief 
	 * @param ActorClass 
	 * @param Tag Tag that must have the actor instance found. If tag is None, the FindActor function is called.
	 * @return The first actor of the ActorClass with the Tag found. Nullptr otherwise.
	 */
	UFUNCTION(BlueprintCallable)
	AActor* FindActorWithTag(TSubclassOf<AActor> ActorClass, FName Tag) const;
	
	/**
	 * @brief 
	 * @param ActorClass 
	 * @param Tag 
	 * @return All actors of the ActorClass with the Tag found. Empty array otherwise.
	 */
	UFUNCTION(BlueprintCallable)
	TArray<AActor*> FindActorsWithTag(TSubclassOf<AActor> ActorClass, FName Tag) const;
	
	UFUNCTION(BlueprintCallable)
	TArray<AActor*> GetAllRegisteredActors() const;

private:
	UPROPERTY()
	TMap<TSubclassOf<AActor>, FWorldRegistryEntry> Data;
};
