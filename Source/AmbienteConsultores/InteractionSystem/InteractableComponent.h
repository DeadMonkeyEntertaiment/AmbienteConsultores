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
	FGameplayTag InteractableTag;

	UPROPERTY(BlueprintReadOnly)
	UInteractionStrategy* InteractionStrategyObject;

	virtual void IStartInteraction_Implementation(AActor* Interactor) override;
	virtual void IEndInteraction_Implementation(AActor* Interactor) override;
	virtual void IOnInteractionGoalAchieved_Implementation(AActor* BaseInteractable) override;
	virtual void IBindToOnInteracted_Implementation(const FOnInteracted& Event) override;
	virtual void IBindToOnInteractionGoalAchieved_Implementation(const FOnInteractionGoalAchieved& Event) override;
	
	UPROPERTY(BlueprintAssignable, Category= "EventDispachers")
	FOnInteractedInternal OnInteracted;
	
	UPROPERTY(BlueprintAssignable, Category= "EventDispachers")
	FOnInteractionGoalAchievedInternal OnInteractionGoalAchieved;
	
protected:
	virtual void BeginPlay() override;	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = InteractableInterface) )
	TSubclassOf<UInteractionStrategy> InteractionStrategyClass;


};
