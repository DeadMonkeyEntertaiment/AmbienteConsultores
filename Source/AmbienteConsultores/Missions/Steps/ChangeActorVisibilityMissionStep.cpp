// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeActorVisibilityMissionStep.h"

void UChangeActorVisibilityMissionStep::Execute(AActor* InPlayerActor)
{
	Super::Execute(InPlayerActor);

	for (auto ActorVisibility : ActorVisibilityList)
	{
		if(!ActorVisibility.Actor.IsNull() && ActorVisibility.Actor.IsValid())
		{
			ActorVisibility.Actor->SetActorHiddenInGame(!ActorVisibility.bIsVisible);
		}
	}
	EndExecution(true);
}
