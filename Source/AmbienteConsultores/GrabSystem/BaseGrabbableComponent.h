// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GrabbableInterface.h"
#include "Components/ActorComponent.h"
#include "BaseGrabbableComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class AMBIENTECONSULTORES_API UBaseGrabbableComponent : public UActorComponent, public IGrabbableInterface
{


private:
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBaseGrabbableComponent();
		
};
