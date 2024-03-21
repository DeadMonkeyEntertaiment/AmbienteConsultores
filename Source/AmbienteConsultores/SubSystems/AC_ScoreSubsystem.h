// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AmbienteConsultores/EvaluationSystem/EvaluationSubsystem.h"
#include "Interfaces/IHttpRequest.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AC_ScoreSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class AMBIENTECONSULTORES_API UAC_ScoreSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	void SendScore(const TArray<FExerciseEvaluation>& Evaluations);

private:
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
