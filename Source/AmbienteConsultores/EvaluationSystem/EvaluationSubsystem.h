// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "EvaluationSubsystem.generated.h"

struct FExerciseSublevel;
class UModuleDataAsset;
class FJsonObject;
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
	int32 FailAttemps;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 SuccessAttemps;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool Win = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Step;

	TSharedPtr<FJsonObject> ToJsonObject() const
	{
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
		
		JsonObject->SetStringField(TEXT("step"), *FString::Printf(TEXT("%s,%f,%d,%d, %d, %s"),
			*Exercise.ToString(), Time, FailAttemps, SuccessAttemps, Step, Win ? TEXT("true") : TEXT("false")));
		return JsonObject;
	}
};

UCLASS(Blueprintable)
class AMBIENTECONSULTORES_API UEvaluationSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	//Esto deberia ser privado, lo pongo publico para testear mas facil
	UPROPERTY(BlueprintReadWrite)
	TArray<UExerciseDataAsset*> SelectedExercises;
	
	//Questionnaire
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<FQuestion> GetQuestions();

	UFUNCTION(BlueprintCallable)
	void ResetQuestionnaire();

	//Activity
	UFUNCTION(BlueprintCallable)
	void StartActivity();
	
	UFUNCTION(BlueprintCallable)
	void NextExercise();
	
	UFUNCTION(BlueprintCallable)
	void FinishActivity();

	//Exercise	
	UFUNCTION(BlueprintCallable)
	void StartExerciseEvaluation();	

	UFUNCTION(BlueprintCallable)
	void AddFailedAttempt();
	
	UFUNCTION(BlueprintCallable)
	void AddSuccessfulAttempt();
	
	UFUNCTION(BlueprintCallable)
	void RetryExercise();
	
	UFUNCTION(BlueprintCallable)
	void FinishExerciseEvaluation(bool &ActivityFinished);		
		
	//Load-unload StreamLevels
	UPROPERTY()
	int LoadLevelIndex;

	UPROPERTY()
	TArray<FExerciseSublevel> LoadWorlds;

	UPROPERTY()
	TArray<FExerciseSublevel> UnloadWorlds;

	UFUNCTION(BlueprintCallable)
	void ManageSubLevelsLoad();

	UFUNCTION(BlueprintCallable)
	void UnloadNextStreamLevel();
	
	UFUNCTION(BlueprintCallable)
	void UnloadStreamLevel(FExerciseSublevel LoadWorld);
	
	UFUNCTION(BlueprintCallable)
	void LoadNextStreamLevel();
	
	UFUNCTION(BlueprintCallable)
	void LoadStreamLevel(FExerciseSublevel LoadWorld);

	//Data
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FString GetSelectedModuleId();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UModuleDataAsset* GetSelectedModule();
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<FExerciseEvaluation> GetExercisesEvaluations();
		
	UFUNCTION(BlueprintCallable)
	UExerciseDataAsset* GetCurrentExercise();

	UFUNCTION(BlueprintCallable)
	void SetSelectedModule(UModuleDataAsset* Module);

	UFUNCTION(BlueprintCallable)
	void AddExercisesToActivity(UExerciseDataAsset* ExerciseData);

	UPROPERTY(BlueprintReadWrite) //should by private
	FExerciseEvaluation CurrentExerciseEvaluation;

	UPROPERTY(BlueprintReadWrite)
	FString AuthToken;
	
private:	
	UPROPERTY()
	int32 UserID;	

	UPROPERTY()
	UModuleDataAsset* SelectedModule;

	UPROPERTY()
	int32 CurrentExerciseNumber;

	UPROPERTY()	
	TArray<FQuestion> Questions;	

	UPROPERTY()
	FName EntryLevelName = "/Game/Maps/MAP_EntryLevel";	

	UPROPERTY()
	TArray<FExerciseEvaluation> ExercisesEvaluations;

	UPROPERTY()
	FVector3d SpawnLocation;
};


