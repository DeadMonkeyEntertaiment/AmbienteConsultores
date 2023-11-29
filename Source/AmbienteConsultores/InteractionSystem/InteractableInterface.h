#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h"


class ABaseInteractable;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractedInternal, AActor*, Interactable);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnInteracted, AActor*, Interactable);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractionGoalAchievedInternal, AActor*, Interactable);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnInteractionGoalAchieved, AActor*, Interactable);

UINTERFACE()
class UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};


class AMBIENTECONSULTORES_API IInteractableInterface
{
	GENERATED_BODY()	
	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	void IStartInteraction(AActor* Interactor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	void IEndInteraction(AActor *Interactor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")//??
	void IOnInteractionGoalAchieved(AActor* Interactable);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	void IBindToOnInteractionGoalAchieved(const FOnInteractionGoalAchieved& Event);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Set Enabled")
	void ISetEnabled(bool NewState);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Set Enabled")
	bool IsEnabled();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	void IBindToOnInteracted(const FOnInteracted& Event);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	void IUnbindFromOnInteracted(const FOnInteracted& Event);
};
