// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MissionStepBase.h"
#include "ActivateInteractionMissionStep.generated.h"

/**
 * 
 */
UCLASS()
class AMBIENTECONSULTORES_API UActivateInteractionMissionStep : public UMissionStepBase
{
	GENERATED_BODY()

public:
	virtual void Execute(AActor* InPlayerActor) override;

private:
	UPROPERTY(EditAnywhere, meta=(EditCondition="bFindUsingRegistry", EditConditionHides))
	TSubclassOf<AActor> ActorClass;
	
	UPROPERTY(EditAnywhere, meta=(EditCondition="bFindUsingRegistry", EditConditionHides))
	FName ActorTag;
	
	UPROPERTY(EditAnywhere, meta=(EditCondition="!bFindUsingRegistry", EditConditionHides))
	TSoftObjectPtr<AActor> TargetActor;
	
	UPROPERTY(EditAnywhere)
	bool bFindUsingRegistry = false;
	
	UPROPERTY(EditAnywhere)
	bool bDisableAfterInteraction = false;
};
