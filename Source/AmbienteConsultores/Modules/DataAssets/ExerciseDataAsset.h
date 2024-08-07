// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ModuleDataAsset.h"
#include "Engine/DataAsset.h"
#include "ExerciseDataAsset.generated.h"

class UExerciseStepStrategyDef;
class APlayerStart;
class ABaseHoldableGrabbable;
class UEvaluationDataAsset;
class UImage;

USTRUCT(BlueprintType)
struct FExerciseSublevel
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UWorld> World;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool MakeVisibleAfterLoad = true;
};

UCLASS(BlueprintType)
class AMBIENTECONSULTORES_API UExerciseDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	FGameplayTag ExerciseTag;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Sublevels")
	TArray<FExerciseSublevel> ExerciseSublevels;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Sublevels")
	TSoftObjectPtr<UWorld> ExerciseActorsSublevel;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	TArray<FQuestion> Questions;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="EPP")
	bool HaveEPP = false;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="EPP")
	bool HaveEPPChecklist = false;
		
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="EPP")
	TArray<FProtectionGear> ExerciseProtectionGear;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Player")
	bool HavePointer;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Player")
	bool HaveMovement;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Player")
	bool HaveGrab;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Player")
	bool EnableRightHand = true;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Player")
	bool EnableLeftHand = true;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Player")
	TSoftObjectPtr<APlayerStart> PlayerStart;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Instructor")
	USkeletalMesh* InstructorSkeletalMesh;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Instructor")
	FInstructorFeedback StartDialog;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Instructor")
	FInstructorFeedback EndDialog;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="Instructor")
	FInstructorFeedback OKDialog;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Instanced, Category="Steps")
	TArray<const UExerciseStepStrategyDef*> SuccessExerciseSteps;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Instanced, Category="Steps")
	TArray<const UExerciseStepStrategyDef*> FailExerciseSteps;
	
};
