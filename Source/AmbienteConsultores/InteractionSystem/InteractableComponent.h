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
public:
	virtual void IEndInteraction_Implementation(AActor* Interactor) override;
	virtual void IStartInteraction_Implementation(AActor* Instigator) override;

private:
	GENERATED_BODY()

public:	
	UInteractableComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag InteractableTag;

	UPROPERTY(BlueprintReadOnly)
	UInteractionStrategy* InteractionStrategyObject;
	
protected:
	virtual void BeginPlay() override;	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = InteractionStrategy) )
	TSubclassOf<UInteractionStrategy> InteractionStrategyClass;
};
