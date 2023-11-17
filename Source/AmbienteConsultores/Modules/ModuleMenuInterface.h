// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ModuleMenuInterface.generated.h"

class UModuleDataAsset;
enum class EExercise : uint8;
enum class EModule : uint8;

DECLARE_DYNAMIC_DELEGATE(FOnButtonClicked);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnModuleSelected, EModule, SelectedModule);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnExercisesSelected, const TArray<EExercise>&,  SelectedExercises);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnHoveredChange, bool, IsHovered);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnCodeEntered, int32, code);



UINTERFACE()
class UModuleMenuInterface : public UInterface
{
	GENERATED_BODY()
};

class AMBIENTECONSULTORES_API IModuleMenuInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
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
	void ISetupExercises(const EModule Module, const TArray<UExerciseDataAsset*>& ModuleExercises);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="VFX")
	void IBindOnHoveredChange(const FOnHoveredChange& Event);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="VFX")
	void IBindOnListItemClicked(const FOnButtonClicked& Event);


};
