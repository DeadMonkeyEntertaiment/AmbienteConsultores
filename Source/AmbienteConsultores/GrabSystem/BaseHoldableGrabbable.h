// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseGrabbable.h"
#include "GameFramework/Actor.h"
#include "BaseHoldableGrabbable.generated.h"

UCLASS(Blueprintable)
class AMBIENTECONSULTORES_API ABaseHoldableGrabbable : public ABaseGrabbable
{
	GENERATED_BODY()

public:
	ABaseHoldableGrabbable();	
};
