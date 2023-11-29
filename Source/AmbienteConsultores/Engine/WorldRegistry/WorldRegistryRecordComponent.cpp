// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldRegistryRecordComponent.h"

#include "WorldRegistrySubsystem.h"

UWorldRegistryRecordComponent::UWorldRegistryRecordComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWorldRegistryRecordComponent::BeginPlay()
{
	Super::BeginPlay();

	UWorldRegistrySubsystem* WorldRegistrySubsystem = GetWorld()->GetSubsystem<UWorldRegistrySubsystem>();
	if(!IsValid(WorldRegistrySubsystem)) return;

	WorldRegistrySubsystem->RegisterActor(GetOwner());
}
