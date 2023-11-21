// Fill out your copyright notice in the Description page of Project Settings.


#include "EnhancedInput.h"

#include "EnhancedInputComponent.h"
#include "InputTriggers.h"
#include "Kismet/GameplayStatics.h"

void UEnhancedInput::SetupInputComponent(UObject* Context, UInputAction* ClickAction, FOnInputAction OnInputActionStart,
                                         FOnInputAction OnInputActionEnd)
{
	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(Context, 0);

	UEnhancedInputComponent* EnhancedInputComponent = PlayerController->FindComponentByClass<UEnhancedInputComponent>();
	
	EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Started, Context, OnInputActionStart.GetFunctionName());
	EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Completed, Context, OnInputActionEnd.GetFunctionName());	
}
