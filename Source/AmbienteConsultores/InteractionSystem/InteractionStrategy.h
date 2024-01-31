#pragma once

#include "CoreMinimal.h"
#include "InteractableInterface.h"
#include "AmbienteConsultores/Utils/BaseTickableObject.h"
#include "InteractionStrategy.generated.h"


UCLASS(Blueprintable, BlueprintType, EditInlineNew)
class AMBIENTECONSULTORES_API UInteractionStrategy : public UBaseTickableObject, public IInteractableInterface
{
	GENERATED_BODY()

public:
	virtual void IStartInteraction_Implementation(AActor* interactor) override;
	virtual void IFinishInteraction_Implementation(AActor* interactor) override;
	virtual bool IIsInteracted_Implementation() override;
	//The other bindings are in the component, this two are here because the interaction strategy is the only who know
	//that the interaction goal was achieved or the interaction was forced to finish 
	virtual void IBindToOnInteractionGoalAchieved_Implementation(const FOnInteractionGoalAchieved& Event) override;
	virtual void IBindToOnForceFinishInteraction_Implementation(const FOnForceFinishInteraction& Event) override;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void InitializeObject(AActor* owner);

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category= "EventDispachers")
	FOnInteractionGoalAchievedInternal OnInteractionGoalAchievedInternal;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category= "EventDispachers")
	FOnForceFinishInteractionInternal OnForceFinishInteractionInternal;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bSupportTwoGrabs;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float GrabTreshold = 0.6;
	
protected:
	UPROPERTY(BlueprintReadWrite)
	AActor *Interactor;

	UPROPERTY(BlueprintReadWrite)
	AActor *Owner;	
		
	UPROPERTY(BlueprintReadWrite)
	bool bInteracted;

	UPROPERTY(BlueprintReadWrite)
	FRotator SpawnRotation;

	UPROPERTY(BlueprintReadWrite)
	FVector SpawnLocation;
};


