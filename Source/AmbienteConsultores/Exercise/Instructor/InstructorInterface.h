// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InstructorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UInstructorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AMBIENTECONSULTORES_API IInstructorInterface
{
	GENERATED_BODY()	
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void InstructorFeedback(FInstructorDialog InstructorDialog);
	
};
