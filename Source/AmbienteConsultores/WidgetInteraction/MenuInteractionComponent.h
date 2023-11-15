// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputAction.h"
#include "MenuInteractionComponent.generated.h"


DECLARE_DYNAMIC_DELEGATE(FOnInputAction_MCISSBP);


UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AMBIENTECONSULTORES_API UMenuInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMenuInteractionComponent();

	

protected:	
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void SetupInputComponent(UInputAction* ClickAction, FOnInputAction_MCISSBP OnInputActionStart, FOnInputAction_MCISSBP OnInputActionEnd);
	
private:
	UPROPERTY()
	UEnhancedInputComponent *EnhancedInputComponent;	
};
