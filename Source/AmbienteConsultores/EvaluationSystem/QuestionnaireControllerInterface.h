// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "QuestionnaireControllerInterface.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnQuestionnaireFinished);


UINTERFACE()
class UQuestionnaireControllerInterface : public UInterface
{
	GENERATED_BODY()
};


class AMBIENTECONSULTORES_API IQuestionnaireControllerInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void IBindToOnQuestionnaireFinished(const FOnQuestionnaireFinished& Event);
};
