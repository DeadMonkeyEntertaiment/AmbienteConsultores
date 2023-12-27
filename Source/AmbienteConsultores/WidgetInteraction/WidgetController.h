// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "WidgetController.generated.h"

class UWidgetComponentGameplayTag;

UCLASS(BlueprintType, Blueprintable, Abstract)
class AMBIENTECONSULTORES_API UWidgetController : public UObject
{
public:
	

private:
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	UWidgetComponentGameplayTag* WidgetComponent;

	UFUNCTION(BlueprintCallable)
	void InitializeWidgetController(UWidgetComponentGameplayTag* WidgetComponentRef);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ToggleWidgetComponentVisibility(bool NewVisibility);

	
	
protected:
	UPROPERTY(BlueprintReadWrite)
	UUserWidget* Widget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> WidgetClass;


	

	

};
