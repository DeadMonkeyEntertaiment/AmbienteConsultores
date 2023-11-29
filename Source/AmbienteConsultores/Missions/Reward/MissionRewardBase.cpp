// Fill out your copyright notice in the Description page of Project Settings.

#include "MissionRewardBase.h"

void UMissionRewardBase::Claim(AActor* PlayerCharacter)
{
	UE_LOG(LogTemp, Log, TEXT("Reward '%s' given to the player"), *GetClass()->GetName())
}

