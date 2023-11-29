// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MissionStepBase.h"
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "MovieSceneSequencePlayer.h"
#include "UObject/Object.h"
#include "PlaySequenceMissionStep.generated.h"

class USequenceSubsystem;
/**
 * 
 */
UCLASS()
class UPlaySequenceMissionStep : public UMissionStepBase
{
	GENERATED_BODY()
public:
	virtual void Execute(AActor* InPlayerActor) override;
	virtual void Cancel() override;
	
	UFUNCTION() void OnSequenceFinished();
private:
	UPROPERTY(EditDefaultsOnly) TObjectPtr<ULevelSequence> SequenceToPlay;
	UPROPERTY(EditDefaultsOnly) FMovieSceneSequencePlaybackSettings SequenceSettings;
	UPROPERTY() USequenceSubsystem* AuxSubsystemRef;
};
