// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AnswerWidgetInterface.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnPressed, int32, AnswerNumber);

UINTERFACE()
class UAnswerWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

class AMBIENTECONSULTORES_API IAnswerWidgetInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void IBindOnAnswerReleased(const FOnPressed& Event);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ISetupWidget(const FQuestion& Question);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void IAnswerFeedback(const bool Correct, const int32 AnswerNumber);


};
