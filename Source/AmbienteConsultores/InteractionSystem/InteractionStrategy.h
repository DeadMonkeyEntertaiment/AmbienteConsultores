#pragma once

#include "CoreMinimal.h"
#include <UObject/Object.h>
#include "InteractableInterface.h"
#include "InteractionStrategy.generated.h"


UCLASS(Blueprintable, BlueprintType, Abstract)
class AMBIENTECONSULTORES_API UInteractionStrategy : public UObject, public FTickableGameObject, public IInteractableInterface
{


private:
	GENERATED_BODY()

public:
	virtual void IStartInteraction_Implementation(AActor* interactor) override;
	//The other bindings are in the component, this two are here because the interaction strategy is the only who know
	//that the interaction goal was achieved or the interaction was forced to finish 
	virtual void IBindToOnInteractionGoalAchieved_Implementation(const FOnInteractionGoalAchieved& Event) override;
	virtual void IBindToOnForceFinishInteraction_Implementation(const FOnForceFinishInteraction& Event) override;
	
	UFUNCTION(BlueprintNativeEvent)
	void InitializeObject(AActor* owner);

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category= "EventDispachers")
	FOnInteractionGoalAchievedInternal OnInteractionGoalAchievedInternal;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category= "EventDispachers")
	FOnForceFinishInteractionInternal OnForceFinishInteractionInternal;
	
protected:
	UPROPERTY(BlueprintReadWrite)
	AActor *Interactor;

	UPROPERTY(BlueprintReadWrite)
	AActor *Owner;	
	
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


