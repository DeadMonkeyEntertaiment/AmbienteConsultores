#pragma once

#include "CoreMinimal.h"
#include <UObject/Object.h>

#include "InteractionStrategy.h"
#include "InteractionStrategyBlueprintable.generated.h"


UCLASS(Blueprintable, BlueprintType, Abstract)
class AMBIENTECONSULTORES_API UInteractionStrategyBlueprintable : public UObject, public FTickableGameObject, public IInteractionStrategy
{
	GENERATED_BODY()
	
public:
	virtual void IStartInteraction_Implementation(AActor* interactor, AActor* interactable) override;

	
protected:
	UPROPERTY(BlueprintReadWrite)
	AActor *Interactor;

	UPROPERTY(BlueprintReadWrite)
	AActor *Interactable;


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

	

private:
	uint32 LastFrameNumberWeTicked = INDEX_NONE;
};


