// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorldRegistry.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "WorldRegistrySubsystem.generated.h"

/**
 * 
 */
UCLASS()
class UWorldRegistrySubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable)
	const UWorldRegistry* GetWorldRegistry() const;

	UFUNCTION(BlueprintCallable)
	void RegisterActor(AActor* Actor);

private:

	UPROPERTY() UWorldRegistry* Registry;
};
