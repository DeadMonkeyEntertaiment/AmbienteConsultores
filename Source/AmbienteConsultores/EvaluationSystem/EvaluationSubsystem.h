// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "EvaluationSubsystem.generated.h"

class UModuleDataAsset;
struct FQuestion;
enum class EExercise : uint8;
enum class EModule : uint8;


USTRUCT(BlueprintType)
struct FExerciseEvaluation
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag Exercise; //description
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	double Time;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 repeats;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool win;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Step;	
};

UCLASS(Blueprintable)
class AMBIENTECONSULTORES_API UEvaluationSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:	
	//Questionnaire
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<FQuestion> GetQuestions();

	UFUNCTION(BlueprintCallable)
	void ResetQuestionnaire();

	//Exercise
	UFUNCTION(BlueprintCallable)
	void AddFailedAttempt();
	
	UFUNCTION(BlueprintCallable)
	void AddSuccessfulAttempt();
	
	UFUNCTION(BlueprintCallable)
	UExerciseDataAsset* GetCurrentExercise();

	//Evaluation
	UFUNCTION(BlueprintCallable)
	void SetSelectedModule(UModuleDataAsset* Module);

	UFUNCTION(BlueprintCallable)
	void AddExercisesToActivity(UExerciseDataAsset* ExerciseData);
	
	UFUNCTION(BlueprintCallable)
	void StartActivity();
	
	UFUNCTION(BlueprintCallable)
	void StartExerciseEvaluation();	
	
	UFUNCTION(BlueprintCallable)
	void FinishExerciseEvaluation(bool &ActivityFinished);		
	
	UFUNCTION(BlueprintCallable)
	void NextExercise(bool &ActivityFinished);

	UFUNCTION(BlueprintCallable)
	void FinishActivity();
	
	//Load-unload StreamLevels
	UPROPERTY()
	int LoadLevelIndex;

	UPROPERTY()
	TArray<TSoftObjectPtr<UWorld>> LoadWorlds;

	UPROPERTY()
	TArray<TSoftObjectPtr<UWorld>> UnloadWorlds;

	UFUNCTION(BlueprintCallable)
	void ManageSubLevelsLoad();

	UFUNCTION(BlueprintCallable)
	void LoadNextStreamLevel();
	
	UFUNCTION(BlueprintCallable)
	void LoadStreamLevel(TSoftObjectPtr<UWorld> LoadWorld);

	UFUNCTION(BlueprintCallable)
	void UnloadNextStreamLevel();
	
	UFUNCTION(BlueprintCallable)
	void UnloadStreamLevel(TSoftObjectPtr<UWorld> LoadWorld);	

	//GetData
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FString GetSelectedModuleId();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<FExerciseEvaluation> GetExercisesEvaluations();
	
private:	
	UPROPERTY()
	int32 UserID;

	UPROPERTY()
	TArray<UExerciseDataAsset*> SelectedExercises;

	UPROPERTY()
	UModuleDataAsset* SelectedModule;

	UPROPERTY()
	int32 CurrentExerciseNumber;

	UPROPERTY()	
	TArray<FQuestion> Questions;	

	UPROPERTY()
	FName EntryLevelName = "/Game/Maps/MAP_EntryLevel";

	UPROPERTY()
	FExerciseEvaluation CurrentExerciseEvaluation;

	UPROPERTY()
	TArray<FExerciseEvaluation> ExercisesEvaluations; 
};


