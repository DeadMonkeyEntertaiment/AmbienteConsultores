// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuInteractionComponent.h"

#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"


UMenuInteractionComponent::UMenuInteractionComponent()
{	
	PrimaryComponentTick.bCanEverTick = true;
}

void UMenuInteractionComponent::BeginPlay()
{	
	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetOwner(), 0);

	EnhancedInputComponent = PlayerController->FindComponentByClass<UEnhancedInputComponent>();
}

void UMenuInteractionComponent::SetupInputComponent(UInputAction* ClickAction, FOnInputAction_MCISSBP OnInputActionStart, FOnInputAction_MCISSBP OnInputActionEnd)
{
	EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Started, this, OnInputActionStart.GetFunctionName());
	EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Completed, this, OnInputActionEnd.GetFunctionName());	
}



