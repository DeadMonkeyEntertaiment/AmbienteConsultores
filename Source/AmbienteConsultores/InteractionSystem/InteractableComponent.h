#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableComponent.generated.h"


class UInteractionStrategyBlueprintable;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class AMBIENTECONSULTORES_API UInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInteractableComponent();

protected:

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StartInteraction(AActor *Interactor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void EndInteraction(AActor *Interactor);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = InteractionStrategy) )
	TSubclassOf<UInteractionStrategyBlueprintable> InteractionStrategyClass;

	UPROPERTY(BlueprintReadOnly)
	UInteractionStrategyBlueprintable *InteractionStrategyObject;
private:
	
	

	
};
