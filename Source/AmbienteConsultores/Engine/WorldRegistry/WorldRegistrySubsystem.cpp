// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldRegistrySubsystem.h"

void UWorldRegistrySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Registry = NewObject<UWorldRegistry>(this);
}

const UWorldRegistry* UWorldRegistrySubsystem::GetWorldRegistry() const
{
	return Registry;
}

void UWorldRegistrySubsystem::RegisterActor(AActor* Actor)
{
	Registry->Register(Actor);
}

