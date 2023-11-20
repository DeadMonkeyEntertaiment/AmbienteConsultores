// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GrabbableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UGrabbableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AMBIENTECONSULTORES_API IGrabbableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void IGrab(AActor* Grabber);

	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void IRelease(AActor* Grabber);
};
