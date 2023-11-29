// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraFadeMissionStep.h"

#include "Kismet/GameplayStatics.h"

void UCameraFadeMissionStep::Execute(AActor* InPlayerActor)
{
	Super::Execute(InPlayerActor);
	Fade();
	EndExecution(true);
}

void UCameraFadeMissionStep::Fade()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(PlayerActor->GetWorld(), 0);
	ensure(PlayerController);
	APlayerCameraManager* CameraManager = PlayerController->PlayerCameraManager;
	ensure(CameraManager);
	CameraManager->StartCameraFade(FromAlpha, ToAlpha, FadeDuration, ColorToFade, bShouldFadeAudio, bHoldWhenFinished);
}