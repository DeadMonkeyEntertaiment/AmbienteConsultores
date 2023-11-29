// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "LevelSequenceActor.h"
#include "AmbienteConsultores/Engine/DataDriven/DataFragmentBase.h"
#include "Reward/MissionRewardBase.h"
#include "Graph/MissionGraph.h"
#include "MissionDataFragment.generated.h"



UENUM()
enum EMissionState
{
	MS_UNDISCOVERED UMETA(DisplayName = "Undiscovered"),
	MS_DISCOVERED UMETA(DisplayName = "Discovered"),
	MS_COMPLETED UMETA(DisplayName = "Completed")
};

/**
 * 
 */
UCLASS()
class UMissionDataFragment : public UDataFragmentBase
{
	GENERATED_BODY()

public:
	/**
	 * @brief Event gameplay tag identifier.
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FGameplayTag MissionTag;
	/**
	 * @brief Set false if you don't want this ascension event to be registered to the AscensionEvent subsystem. Also,
	 * if you have an AscensionEventActor in the world with this configuration, it wont work.
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	bool bIsEnabled = true;
	/**
	 * @brief Starting mission state. UNDISCOVERED is default state.
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TEnumAsByte<EMissionState> StartingMissionState = MS_UNDISCOVERED;
	
	/**
	 * @brief Begin mission trigger
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Triggers", meta=(MustImplement="TriggerActorInterface"))
	TSoftObjectPtr<AActor> StartTrigger;
	/**
	 * @brief End mission trigger
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Triggers", meta=(MustImplement="TriggerActorInterface"))
	TSoftObjectPtr<AActor> EndTrigger;
	/**
	 * @brief Should mission prevent player to run?. 
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Block")
	bool bIsBlockerEvent = false;
	/**
	 * @brief Blocker actors of a blocking mission.
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Block", meta=(EditCondition="bIsBlockerEvent",EditConditionHides))
	TArray<TSoftObjectPtr<AActor>> BlockingActors;
	/**
	 * @brief Sequence to play the first time the player starts the mission. (Optional)
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Sequences & Fx")
	TObjectPtr<ULevelSequence> IntroSequence;
	/**
	 * @brief Intro Sequence player settings.
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Sequences & Fx", meta=(EditCondition= "IntroSequence != nullptr", EditConditionHides))
	FMovieSceneSequencePlaybackSettings IntroSequenceSettings;


	/**
	 * @brief Mission Graph
	*/
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Steps")
	TObjectPtr<UMissionGraph> MissionGraph;
	
	
	/**
	 * @brief Sequence to play after the player ends the mission. (Optional)
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Sequences & Fx")
	TObjectPtr<ULevelSequence> OutroSequence;
	
	/**
	 * @brief Outro Sequence player settings.
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Sequences & Fx", meta=(EditCondition= "OutroSequence != nullptr", EditConditionHides))
	FMovieSceneSequencePlaybackSettings OutroSequenceSettings;
	
	/**
	 * @brief Sfx to play when the player starts the mission. (Optional)
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Sequences & Fx")
	TObjectPtr<USoundBase> StartSFX;

	/**
	 * @brief Music to play when the player starts the mission. (Optional)
	*/
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Sequences & Fx")
	TObjectPtr<USoundBase> MissionMusic;
	/**
	 * @brief Sfx to play when the player starts the mission. (Optional)
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Sequences & Fx")
	TObjectPtr<USoundBase> EndSFX;
	/**
	 * @brief Sublevels to activate when the mission is completed.
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Event End")
	TArray<TSoftObjectPtr<UWorld>> LevelsToActivate;
	
	/**
	 * @brief Sublevels to deactivate when the mission is completed.
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Event End")
	TArray<TSoftObjectPtr<UWorld>> LevelsToDeactivate;
	
	/**
	 * @brief Whether activate "LevelsToActivate" and deactivate "LevelsToDeactivate"
	 * instantly after the mission is completed or the next time the map is loaded.
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Event End")
	bool ApplyLevelChangesOnCompleted = false;
	
	/**
	 * @brief Level to transition after the mission ended.
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Event End")
	TSoftObjectPtr<UWorld> LevelToLoad;
	
	/**
	 * @brief Reward to give to the player when the event is completed
	 */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Instanced, Category="Event End")
	TArray<TObjectPtr<UMissionRewardBase>> RewardClass;
};
