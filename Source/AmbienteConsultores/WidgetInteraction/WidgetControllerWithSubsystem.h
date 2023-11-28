// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WidgetController.h"
#include "AmbienteConsultores/EvaluationSystem/EvaluationSubsystem.h"
#include "AmbienteConsultores/Modules/ActivitySubsystem.h"
#include "WidgetControllerWithSubsystem.generated.h"


UCLASS()
class AMBIENTECONSULTORES_API UWidgetControllerWithSubsystem : public UWidgetController
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable,BlueprintPure)
	UEvaluationSubsystem* GetEvaluationSubsystem();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	APlayerController* GetPlayerController();
};
