// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AmbienteConsultores/Modules/DataAssets/ModuleDataAsset.h"
#include "Engine/DataAsset.h"
#include "InstructorGeneralDialogsDataAsset.generated.h"



UCLASS(BlueprintType)
class AMBIENTECONSULTORES_API UInstructorGeneralDialogsDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	TMap<FString, FInstructorFeedback> InstructorGeneralDialogues;	
};
