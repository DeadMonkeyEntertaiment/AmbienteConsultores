#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h"


class ABaseInteractable;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInteractionStartInternal, AActor*, Interactor, AActor*, Interactable);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnInteractionStart, AActor*, Interactor, AActor*, Interactable);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInteractionFinishedInternal, AActor*, Interactor, AActor*, Interactable);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnInteractionFinished, AActor*, Interactor, AActor*, Interactable);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInteractionGoalAchievedInternal, AActor*, Interactor, AActor*, Interactable);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnInteractionGoalAchieved, AActor*, Interactor, AActor*, Interactable);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnForceFinishInteractionInternal, AActor*, Interactor, AActor*, Interactable);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnForceFinishInteraction, AActor*, Interactor, AActor*, Interactable);

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
	void IBindToOnInteractionStarted(const FOnInteractionStart& Event);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	void IStartInteraction(AActor* Interactor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	void IFinishInteraction(AActor *Interactor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	void IOnInteractionGoalAchieved(AActor* Interactor, AActor* Interactable);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	void IBindToOnInteractionGoalAchieved(const FOnInteractionGoalAchieved& Event);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	void IOnForceFinishInteraction(AActor* Interactor, AActor* Interactable);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	void IBindToOnForceFinishInteraction(const FOnForceFinishInteraction& Event);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Set Enabled")
	void ISetEnabled(bool NewState);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Set Enabled")
	bool IsEnabled();

	

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	void IBindToOnInteractionFinished(const FOnInteractionFinished& Event);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	void IUnbindFromOnInteracted(const FOnInteractionStart& Event);
};
