// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaySkeletalAnimationMissionStep.h"

void UPlaySkeletalAnimationMissionStep::Execute(AActor* InPlayerActor)
{
	Super::Execute(InPlayerActor);

	if(SkeletalMeshActor.IsNull())
	{
		EndExecution(false);
		return;
	}

	const auto& SkeletalMeshComponent = SkeletalMeshActor->GetSkeletalMeshComponent();
	SkeletalMeshComponent->SetPlayRate(PlayRate);
	SkeletalMeshComponent->Play(false);
	EndExecution(true);
}
