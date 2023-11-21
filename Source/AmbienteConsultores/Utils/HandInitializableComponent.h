// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InitializableInterface.h"
#include "Components/ActorComponent.h"
#include "HandInitializableComponent.generated.h"



UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class AMBIENTECONSULTORES_API UHandInitializableComponent : public UActorComponent, public IInitializableInterface
{
	GENERATED_BODY()

public:
	UHandInitializableComponent();
};
