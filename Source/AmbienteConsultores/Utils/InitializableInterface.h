// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InputAction.h"
#include "InitializableInterface.generated.h"


UINTERFACE()
class UInitializableInterface : public UInterface
{
	GENERATED_BODY()
};


class AMBIENTECONSULTORES_API IInitializableInterface
{
	GENERATED_BODY()
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Initializable")
	void IInitializeComponent(EControllerHand ControllerType, bool &Initialized);

};
