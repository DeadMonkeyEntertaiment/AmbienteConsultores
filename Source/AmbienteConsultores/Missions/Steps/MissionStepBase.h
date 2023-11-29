// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AmbienteConsultores/Missions/Graph/MissionNode.h"
#include "UObject/Object.h"
#include "MissionStepBase.generated.h"

class UMissionStepBase;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStepDone, UMissionStepBase*, Step, bool, bSuccess);


/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, Abstract, EditInlineNew)
class UMissionStepBase : public UMissionNode
{
	GENERATED_BODY()

public:
	UFUNCTION() virtual void Execute(AActor* InPlayerActor);
	UFUNCTION() virtual void Cancel();
	UFUNCTION() virtual FString ToString();
	
	UPROPERTY() FOnStepDone OnStepDone;
protected:
	UFUNCTION() virtual void EndExecution(bool bSuccess);
	UPROPERTY() AActor* PlayerActor;

};