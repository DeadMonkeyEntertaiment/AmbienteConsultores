#pragma once

#include "CoreMinimal.h"
#include "GameplayTags.h"
#include "Components/ActorComponent.h"
#include "InteractableComponent.generated.h"


class UInteractionStrategyBlueprintable;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class AMBIENTECONSULTORES_API UInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInteractableComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag InteractableTag;
	
protected:

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StartInteraction(AActor *Interactor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void EndInteraction(AActor *Interactor);
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnInteractionGoalAchieved();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (MustImplement = InteractionStrategy) )
	TSubclassOf<UInteractionStrategyBlueprintable> InteractionStrategyClass;

	UPROPERTY(BlueprintReadOnly)
	UInteractionStrategyBlueprintable *InteractionStrategyObject;


	
};
