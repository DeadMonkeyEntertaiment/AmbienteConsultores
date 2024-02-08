#pragma once

#include "CoreMinimal.h"
#include "GameplayTags.h"
#include "InteractableInterface.h"
#include "Components/ActorComponent.h"
#include "InteractableComponent.generated.h"


class UInteractionStrategy;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStrategyInitialized, UInteractionStrategy*, InteractionStrategy);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class AMBIENTECONSULTORES_API UInteractableComponent : public UActorComponent, public IInteractableInterface
{
	GENERATED_BODY()

public:	
	UInteractableComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer InteractableTags;	
	
	UPROPERTY(BlueprintReadOnly)
	AActor* NewInteractor;

	UPROPERTY(BlueprintReadWrite)
	bool InteractionGopalAchieved;
	
	virtual bool IIsEnabled_Implementation() override;
	virtual void ISetEnabled_Implementation(bool NewState) override;
	virtual bool IIsInteracted_Implementation() override;
	
	virtual void IStartInteraction_Implementation(AActor* Interactor) override;
	virtual void IBindToOnInteractionStarted_Implementation(const FOnInteractionStarted& Event) override;
	virtual void IUnbindToOnInteractionStarted_Implementation(const FOnInteractionStarted& Event) override;

	virtual void IFinishInteraction_Implementation(AActor* Interactor) override;
	virtual void IBindToOnInteractionFinished_Implementation(const FOnInteractionFinished& Event) override;
	virtual void IUnbindToOnInteractionFinished_Implementation(const FOnInteractionFinished& Event) override;

	virtual void IOnInteractionGoalAchieved_Implementation(AActor* Interactor, AActor* Interactable) override;
	virtual void IBindToOnInteractionGoalAchieved_Implementation(const FOnInteractionGoalAchieved& Event) override;
	virtual void IUnbindToOnInteractionGoalAchieved_Implementation(const FOnInteractionGoalAchieved& Event) override;
	
	virtual void IBindToOnForceFinishInteraction_Implementation(const FOnForceFinishInteraction& Event) override;
	virtual void IOnForceFinishInteraction_Implementation(AActor* Interactor, AActor* Interactable) override;
	
	UPROPERTY(BlueprintAssignable, Category= "EventDispachers")
	FOnInteractionStartedInternal OnInteractionStartedInternal;

	UPROPERTY(BlueprintAssignable, Category= "EventDispachers")
	FOnInteractionFinishedInternal OnInteractionFinishedInternal;
	
	UPROPERTY(BlueprintAssignable, Category= "EventDispachers")
	FOnInteractionGoalAchievedInternal OnInteractionGoalAchievedInternal;

	UPROPERTY(BlueprintAssignable, Category= "EventDispachers")
	FOnForceFinishInteractionInternal OnForceFinishInteractionInternal;
	
	UPROPERTY(BlueprintAssignable, Category= "EventDispachers")
	FOnStrategyInitialized OnStrategyInitialized;
	
	
protected:
	virtual void BeginPlay() override;	
	
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite)
	UInteractionStrategy* InteractionStrategy;

	UPROPERTY(BlueprintReadWrite)
	bool bEnable = true;

	UPROPERTY()
	bool bInteracted = true;	
};


