// Fill out your copyright notice in the Description page of Project Settings.


#include "QuitGameMissionStep.h"

#include "Kismet/KismetSystemLibrary.h"


void UQuitGameMissionStep::Execute(AActor* InPlayerActor)
{
	Super::Execute(InPlayerActor);

	EndExecution(true);
	// FGenericPlatformMisc::RequestExit(true);

	UKismetSystemLibrary::QuitGame(InPlayerActor->GetWorld(),
		nullptr,
		EQuitPreference::Quit, true);
	
}
