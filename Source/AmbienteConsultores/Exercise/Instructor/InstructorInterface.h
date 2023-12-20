// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AmbienteConsultores/Modules/DataAssets/ExerciseDataAsset.h"
#include "UObject/Interface.h"
#include "InstructorInterface.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInstructorFeedbackDoneInternal);
DECLARE_DYNAMIC_DELEGATE(FOnInstructorFeedbackDone);

UINTERFACE()
class UInstructorInterface : public UInterface
{
	GENERATED_BODY()
};

class AMBIENTECONSULTORES_API IInstructorInterface
{
	GENERATED_BODY()	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void IDoInstructorFeedback(FInstructorFeedback InstructorFeedback);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void IBindToOnInstructorFeedbackDone(const FOnInstructorFeedbackDone &Event);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void IUnbindFromOnInstructorFeedbackDone(const FOnInstructorFeedbackDone &Event);
};
