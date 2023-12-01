#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h"


class ABaseInteractable;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInteractionStartedInternal, AActor*, Interactor, AActor*, Interactable);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnInteractionStarted, AActor*, Interactor, AActor*, Interactable);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInteractionFinishedInternal, AActor*, Interactor, AActor*, Interactable);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnInteractionFinished, AActor*, Interactor, AActor*, Interactable);

//This is to let know the exercise manager that the interaction goal was achieved
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInteractionGoalAchievedInternal, AActor*, Interactor, AActor*, Interactable);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnInteractionGoalAchieved, AActor*, Interactor, AActor*, Interactable);

//This is to let know the interactor that the interaction was force finished
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
	//Start Interaction	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	void IStartInteraction(AActor* Interactor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact Binding")
	void IBindToOnInteractionStarted(const FOnInteractionStarted& Event);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact Binding")
	void IUnbindToOnInteractionStarted(const FOnInteractionStarted& Event);
	
	//Finish Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	void IFinishInteraction(AActor *Interactor);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact Binding")
	void IBindToOnInteractionFinished(const FOnInteractionFinished& Event);	

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact Binding")
	void IUnbindToOnInteractionFinished(const FOnInteractionFinished& Event);	
	
	//Force Finish
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	void IOnForceFinishInteraction(AActor* Interactor, AActor* Interactable);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact Binding")
	void IBindToOnForceFinishInteraction(const FOnForceFinishInteraction& Event);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact Binding")
	void IOnBindToOnForceFinishInteraction(const FOnForceFinishInteraction& Event);
	
	//Interaction Goal
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	void IOnInteractionGoalAchieved(AActor* Interactor, AActor* Interactable);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact Binding")
	void IBindToOnInteractionGoalAchieved(const FOnInteractionGoalAchieved& Event);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact Binding")
	void IUnbindToOnInteractionGoalAchieved(const FOnInteractionGoalAchieved& Event);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Set Enabled")
	void ISetEnabled(bool NewState);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Set Enabled")
	bool IIsEnabled();	
};
