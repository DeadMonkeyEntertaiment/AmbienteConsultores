// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MissionStepBase.h"
#include "StateMachineTogglerStep.generated.h"

/**
 * 
 */
UCLASS()
class AMBIENTECONSULTORES_API UStateMachineTogglerStep : public UMissionStepBase
{
	GENERATED_BODY()

public:
	virtual void Execute(AActor* InPlayerActor) override;

	UPROPERTY(EditAnywhere)
	TArray<TSoftObjectPtr<AActor>> Mannequins;

	/*
	 * Turns on the IA State machine if true. Turns off if false. 
	 */
	UPROPERTY(EditAnywhere)
	bool bShouldStartStateMachine = true;
};
