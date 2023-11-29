// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MissionStepBase.h"
#include "ModifyAudioComponentMissionStep.generated.h"

/**
 * 
 */
UCLASS()
class AMBIENTECONSULTORES_API UModifyAudioComponentMissionStep : public UMissionStepBase
{
	GENERATED_BODY()

public:
	virtual void Execute(AActor* InPlayerActor) override;

protected:
	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<AActor> AudioComponentOwner;

	UPROPERTY(EditAnywhere)
	float NewPitchMultiplier;
	UPROPERTY(EditAnywhere)
	float NewVolumeMultiplier;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> NewSound;
	UPROPERTY(EditAnywhere)
	FSoundAttenuationSettings NewAttenuationSettings;
};
