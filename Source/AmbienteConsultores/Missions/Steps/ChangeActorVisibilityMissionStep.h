// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MissionStepBase.h"
#include "ChangeActorVisibilityMissionStep.generated.h"


USTRUCT(BlueprintType)
struct FNewActorVisibilityData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TSoftObjectPtr<AActor> Actor;
	UPROPERTY(EditAnywhere) bool bIsVisible = true;
	
};

/**
 * 
 */
UCLASS()
class AMBIENTECONSULTORES_API UChangeActorVisibilityMissionStep : public UMissionStepBase
{
	GENERATED_BODY()

public:
	virtual void Execute(AActor* InPlayerActor) override;

	UPROPERTY(EditAnywhere)
	TArray<FNewActorVisibilityData> ActorVisibilityList;

};
