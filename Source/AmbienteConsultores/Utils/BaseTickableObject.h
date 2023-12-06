// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BaseTickableObject.generated.h"


UCLASS(Abstract)
class AMBIENTECONSULTORES_API UBaseTickableObject : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

protected:

	UFUNCTION(BlueprintImplementableEvent)
	void ObjectTick(float DeltaTime);
	
	//Make object tickable
	virtual void Tick(float DeltaTime) override;	
	virtual ETickableTickType GetTickableTickType() const override
	{
		return ETickableTickType::Conditional;
	}
	virtual TStatId GetStatId() const override
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FMyTickableThing, STATGROUP_Tickables);
	}
	virtual bool IsTickableWhenPaused() const override
	{
		return true;
	}
	virtual bool IsTickableInEditor() const override
	{
		return false;
	}
};
