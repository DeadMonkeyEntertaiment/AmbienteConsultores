// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MissionStepBase.h"
#include "Animation/SkeletalMeshActor.h"
#include "PlaySkeletalAnimationMissionStep.generated.h"

/**
 * 
 */
UCLASS()
class AMBIENTECONSULTORES_API UPlaySkeletalAnimationMissionStep : public UMissionStepBase
{
	GENERATED_BODY()

public:
	virtual void Execute(AActor* InPlayerActor) override;

private:
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<ASkeletalMeshActor> SkeletalMeshActor;

	UPROPERTY(EditAnywhere)
	float PlayRate = 1;
};
