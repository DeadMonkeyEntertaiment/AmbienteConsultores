// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LevelSequencePlayer.h"
#include "LevelSequence.h"
#include "SequenceSubsystem.generated.h"

DECLARE_DYNAMIC_DELEGATE(FFinishedCutsceneDelegate);

/**
 * 
 */
UCLASS()
class USequenceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	USequenceSubsystem();

protected:
	UPROPERTY()
	ULevelSequencePlayer* MainSequencePlayer;

	UPROPERTY()
	TArray<ULevelSequence*> SequenceQueue;

	UPROPERTY()
	TMap<FString, FFinishedCutsceneDelegate> DelegateMap;

	UPROPERTY()
	TMap<FString, FMovieSceneSequencePlaybackSettings> PlaybackSettingsMap;

	UFUNCTION()
	void OnSequenceFinished();

	void PlayCutscene(ULevelSequence* Sequence, FMovieSceneSequencePlaybackSettings PlaybackSettings = FMovieSceneSequencePlaybackSettings());

public:
	void PlayOrderedCutscene(ULevelSequence* Sequence, FMovieSceneSequencePlaybackSettings PlaybackSettings = FMovieSceneSequencePlaybackSettings());

	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "OnFinishedDelegate"))
	void PlayOrderedCutscene(ULevelSequence* Sequence, const FFinishedCutsceneDelegate& OnFinishedDelegate, FMovieSceneSequencePlaybackSettings PlaybackSettings = FMovieSceneSequencePlaybackSettings());

	UFUNCTION(BlueprintCallable)
	void SkipCutscene();
};