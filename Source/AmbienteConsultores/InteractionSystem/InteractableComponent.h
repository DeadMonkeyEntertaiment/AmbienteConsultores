#pragma once

#include "CoreMinimal.h"
#include "GameplayTags.h"
#include "InteractableInterface.h"
#include "Components/ActorComponent.h"
#include "InteractableComponent.generated.h"


class UInteractionStrategy;



UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class AMBIENTECONSULTORES_API UInteractableComponent : public UActorComponent, public IInteractableInterface
{
	GENERATED_BODY()

public:	
	UInteractableComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer InteractableTags;

	UPROPERTY(BlueprintReadOnly)
	UInteractionStrategy* InteractionStrategyObject;

	virtual void IBindToOnInteractionStarted_Implementation(const FOnInteractionStart& Event) override;
	virtual void IStartInteraction_Implementation(AActor* Interactor) override;

	virtual void IBindToOnInteractionFinished_Implementation(const FOnInteractionFinished& Event) override;
	virtual void IFinishInteraction_Implementation(AActor* Interactor) override;
	
	virtual void IBindToOnInteractionGoalAchieved_Implementation(const FOnInteractionGoalAchieved& Event) override;
	virtual void IOnInteractionGoalAchieved_Implementation(AActor* Interactor, AActor* Interactable) override;
	
	virtual void IBindToOnForceFinishInteraction_Implementation(const FOnForceFinishInteraction& Event) override;
	virtual void IOnForceFinishInteraction_Implementation(AActor* Interactor, AActor* Interactable) override;
	
	UPROPERTY(BlueprintAssignable, Category= "EventDispachers")
	FOnInteractionStartInternal OnInteractionStart;

	UPROPERTY(BlueprintAssignable, Category= "EventDispachers")
	FOnInteractionFinishedInternal OnInteractionFinished;
	
	UPROPERTY(BlueprintAssignable, Category= "EventDispachers")
	FOnInteractionGoalAchievedInternal OnInteractionGoalAchieved;

	UPROPERTY(BlueprintAssignable, Category= "EventDispachers")
	FOnForceFinishInteractionInternal OnForceFinishInteraction;
	
protected:
	virtual void BeginPlay() override;	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = InteractableInterface) )
	TSubclassOf<UInteractionStrategy> InteractionStrategyClass;


};


