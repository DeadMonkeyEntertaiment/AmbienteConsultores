// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldRegistry.h"

void UWorldRegistry::Register(AActor* Actor)
{
	if(!IsValid(Actor)) return;

	if(Data.Contains(Actor->GetClass()))
	{
		Data[Actor->GetClass()].RegisteredActors.Add(Actor);
		return;
	}
	Data.Add(Actor->GetClass(), FWorldRegistryEntry(Actor));
}

void UWorldRegistry::Unregister(AActor* Actor)
{
	if (!IsValid(Actor)) return;
	if (!Data.Contains(Actor->GetClass())) return;
	if (!Data[Actor->GetClass()].RegisteredActors.Contains(Actor)) return;
	Data[Actor->GetClass()].RegisteredActors.Remove(Actor);
}

AActor* UWorldRegistry::FindActor(TSubclassOf<AActor> ActorClass, bool ExhaustiveSearch) const
{
	if (ExhaustiveSearch)
	{
		TArray<TSubclassOf<AActor>> RegisteredClasses;
		Data.GenerateKeyArray(RegisteredClasses);

		for (TSubclassOf<AActor> RegisteredClass : RegisteredClasses)
			if (RegisteredClass->IsChildOf(ActorClass) && Data[RegisteredClass].RegisteredActors.Num() > 0)
				return Data[RegisteredClass].RegisteredActors[0];
	}
	else
	{
		if (Data.Contains(ActorClass) && Data[ActorClass].RegisteredActors.Num() > 0)
			return Data[ActorClass].RegisteredActors[0];
	}
	return nullptr;
}

TArray<AActor*> UWorldRegistry::FindActors(TSubclassOf<AActor> ActorClass) const
{
	if(!Data.Contains(ActorClass)) return TArray<AActor*>();
	return Data[ActorClass].RegisteredActors;
}

AActor* UWorldRegistry::FindActorWithTag(TSubclassOf<AActor> ActorClass, FName Tag) const
{
	if(!Data.Contains(ActorClass) || Data[ActorClass].RegisteredActors.Num() == 0) return nullptr;

	if(Tag == "")
		return FindActor(ActorClass);

	AActor* Result = nullptr;
	for (auto Actor : Data[ActorClass].RegisteredActors)
	{
		if(Actor->ActorHasTag(Tag))
		{
			Result = Actor;
			break;
		}
	}
	return Result;
}

TArray<AActor*> UWorldRegistry::FindActorsWithTag(TSubclassOf<AActor> ActorClass, FName Tag) const
{
	if(!Data.Contains(ActorClass)) return TArray<AActor*>();

	TArray<AActor*> Result;
	for (auto Actor : Data[ActorClass].RegisteredActors)
	{
		if(Actor->ActorHasTag(Tag))
		{
			Result.Add(Actor);
		}
	}
	return Result;
}

TArray<AActor*> UWorldRegistry::GetAllRegisteredActors() const
{
	TArray<AActor*> Result;

	TArray<TSubclassOf<AActor>> RegisteredClasses;
	Data.GenerateKeyArray(RegisteredClasses);

	for (auto RegisteredClass : RegisteredClasses)
		for (auto Actor : Data[RegisteredClass].RegisteredActors)
			Result.Add(Actor);

	return Result;
}
