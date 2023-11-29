// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MissionStepBase.h"
#include "CameraFadeMissionStep.generated.h"

/**
 * 
 */
UCLASS()
class AMBIENTECONSULTORES_API UCameraFadeMissionStep : public UMissionStepBase
{
	GENERATED_BODY()
	
public:
	virtual void Execute(AActor* InPlayerActor) override;

protected:

	UFUNCTION()
	void Fade();
	
	UPROPERTY(EditAnywhere, Category="Fade")
	float FadeDuration = 1;
	UPROPERTY(EditAnywhere, Category="Fade")
	float FromAlpha;
	UPROPERTY(EditAnywhere, Category="Fade")
	float ToAlpha;
	UPROPERTY(EditAnywhere, Category="Fade")
	FLinearColor ColorToFade = FLinearColor::Black;
	UPROPERTY(EditAnywhere, Category="Fade")
	bool bHoldWhenFinished;
	UPROPERTY(EditAnywhere, Category="Fade")
	bool bShouldFadeAudio;
};
