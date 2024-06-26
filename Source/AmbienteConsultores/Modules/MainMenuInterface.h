// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "MainMenuInterface.generated.h"

class UModuleDataAsset;

DECLARE_DYNAMIC_DELEGATE(FOnButtonClicked);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnModuleSelected, FGameplayTag, SelectedModule);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnExercisesSelected, const TArray<FGameplayTag>&,  SelectedExercises);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnHoveredChange, bool, IsHovered);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnCodeEntered, int32, code);



UINTERFACE()
class UMainMenuInterface : public UInterface
{
	GENERATED_BODY()
};

class AMBIENTECONSULTORES_API IMainMenuInterface
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void IBindToOnBackClicked(const FOnButtonClicked& Event);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void IBindToOnModuleSelected(const FOnModuleSelected& Event);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void IBindToOnExercisesSelected(const FOnExercisesSelected& Event);	

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void IBindToOnUserCodeEntered(const FOnCodeEntered& Event);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ISetupModules(const TArray<UModuleDataAsset*>& ModuleExercises);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ISetupExercises(const FGameplayTag Module, const TArray<UExerciseDataAsset*>& ModuleExercises);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void IShowErrorMessage(const FString& ErrorMessage);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="VFX")
	void IBindToOnHoveredChange(const FOnHoveredChange& Event);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="VFX")
	void IBindToOnListItemClicked(const FOnButtonClicked& Event);
};
