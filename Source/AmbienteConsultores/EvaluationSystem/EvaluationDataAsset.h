// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EvaluationDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FQuestion
{
	GENERATED_BODY()
	UPROPERTY(meta=(MultiLine), EditAnywhere, BlueprintReadOnly)
	FText Question;	
	
	UPROPERTY(meta=(MultiLine), EditAnywhere, BlueprintReadOnly)
	TArray<FText> Answers;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 CorrectAnswer;	
};


UCLASS(BlueprintType)
class AMBIENTECONSULTORES_API UEvaluationDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FQuestion> Questions;	
	
};
