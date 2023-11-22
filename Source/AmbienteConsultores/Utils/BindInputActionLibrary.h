// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BindInputActionLibrary.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnInputActionEvent);


UCLASS()
class AMBIENTECONSULTORES_API UBindInputActionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	static void BindInputAction(UObject* Context, UInputAction* InputAction, FOnInputActionEvent OnInputActionStart, FOnInputActionEvent OnInputActionEnd);
};
