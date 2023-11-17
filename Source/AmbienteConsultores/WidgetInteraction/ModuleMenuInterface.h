// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ModuleMenuInterface.generated.h"


enum class EExercise : uint8;
enum class EModule : uint8;
DECLARE_DYNAMIC_DELEGATE(FOnStart);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnModuleSelected, EModule, SelectedModule);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnExerciseSelected, EExercise, SelectedExercise);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnPressed2, int32, AnswerNumber);


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
	void IBindOnStart(const FOnStart& Event);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void IBindOnModuleSelected(const FOnModuleSelected& Event);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void IBindOnExerciseSelected(const FOnExerciseSelected& Event);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void IBindOnAnswerReleased(const FOnPressed2& Event);
};
