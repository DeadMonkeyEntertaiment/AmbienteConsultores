// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InitializableInterface.h"
#include "Components/ActorComponent.h"
#include "InputAction.h"
#include "HandInitializableComponent.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnInputActionEvent);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class AMBIENTECONSULTORES_API UHandInitializableComponent : public UActorComponent, public IInitializableInterface
{
	GENERATED_BODY()

public:
	UHandInitializableComponent();

protected:

	UFUNCTION(BlueprintCallable)
	void BindInputAction(UInputAction* InputAction, FOnInputActionEvent OnInputActionStart,
												  FOnInputActionEvent OnInputActionEnd);	
};
