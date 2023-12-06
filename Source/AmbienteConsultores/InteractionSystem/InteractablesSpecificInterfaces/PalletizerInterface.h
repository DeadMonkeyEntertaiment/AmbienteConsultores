// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PalletizerInterface.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnPalletizerInteralAction);

UINTERFACE()
class UPalletizerInterface : public UInterface
{
	GENERATED_BODY()
};


class AMBIENTECONSULTORES_API IPalletizerInterface
{
	GENERATED_BODY()

	
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Binding")
	void IBindToOnPlayerInPosition(const FOnPalletizerInteralAction& Event);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Binding")
	void IBindToOnLoadInPosition(const FOnPalletizerInteralAction& Event);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Binding")
	void IBindToOnRose(const FOnPalletizerInteralAction& Event);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Binding")
	void IBindToOnLowered(const FOnPalletizerInteralAction& Event);
};
