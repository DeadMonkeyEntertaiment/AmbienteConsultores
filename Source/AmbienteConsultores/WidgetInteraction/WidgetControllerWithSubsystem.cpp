// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetControllerWithSubsystem.h"

#include "Kismet/GameplayStatics.h"

UEvaluationSubsystem* UWidgetControllerWithSubsystem::GetEvaluationSubsystem()
{
	return GetWorld()->GetGameInstance()->GetSubsystem<UEvaluationSubsystem>();
}

UActivitySubsystem* UWidgetControllerWithSubsystem::GetActivitySubsystem()
{
	return GetWorld()->GetGameInstance()->GetSubsystem<UActivitySubsystem>();
}

APlayerController* UWidgetControllerWithSubsystem::GetPlayerController()
{
	APlayerController* Controller =  UGameplayStatics::GetPlayerController(GetWorld(), 0);
	return Controller;
}



