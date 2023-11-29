// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MissionStepBase.h"
#include "UObject/Object.h"
#include "PlayerTriggerMissionStep.generated.h"

/**
 * 
 */
UCLASS()
class UPlayerTriggerMissionStep : public UMissionStepBase
{
	GENERATED_BODY()
public:
	virtual void Execute(AActor* Owner) override;
	virtual void Cancel() override;
#if WITH_EDITOR
	virtual FText GetNodeTitle() const override;
#endif

private:
	UFUNCTION() void OnTriggerExecuted(FTriggerInteractionInfo InteractionInfo) ;
	UPROPERTY(EditDefaultsOnly, meta=(AllowedClasses="TriggerActorInterface")) TSoftObjectPtr<AActor> Trigger;
	/**
	 * @brief The step ends when the player exits the trigger if true. When false, the step ends when the player enters the trigger.
	 */
	UPROPERTY(EditDefaultsOnly) bool bFinishOnExit = false;
};
