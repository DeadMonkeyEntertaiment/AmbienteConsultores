// Fill out your copyright notice in the Description page of Project Settings.


#include "BindInputActionLibrary.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"


void UBindInputActionLibrary::BindInputActionLibrary(UObject* Context, UInputAction* InputAction, FOnInputActionEventLibrary OnInputActionStart,
                                                  FOnInputActionEventLibrary OnInputActionEnd)
{
	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(Context, 0);
	UEnhancedInputComponent* EnhancedInputComponent = PlayerController->FindComponentByClass<UEnhancedInputComponent>();
	
	EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Started, Context, OnInputActionStart.GetFunctionName());
	EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Completed, Context, OnInputActionEnd.GetFunctionName());	
}
