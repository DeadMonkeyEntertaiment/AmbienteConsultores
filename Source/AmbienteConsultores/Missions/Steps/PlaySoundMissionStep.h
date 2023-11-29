// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MissionStepBase.h"
#include "PlaySoundMissionStep.generated.h"

/**
 * 
 */
UCLASS()
class AMBIENTECONSULTORES_API UPlaySoundMissionStep : public UMissionStepBase
{
	GENERATED_BODY()

public:
	virtual void Execute(AActor* InPlayerActor) override;
	virtual void Cancel() override;

private:
	
	UFUNCTION()
	void OnAudioFinished();

	UFUNCTION()
	void StopSound(bool bShouldDestroyComponent = false);
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> Sound;

	/*
	 * If value = 0, the sound will play 'til the end.
	 */
	UPROPERTY(EditAnywhere)
	float StopAfterSeconds = 0;

	UPROPERTY(EditAnywhere)
	float FadeOutDuration = 0;
	
	UPROPERTY(EditAnywhere)
	float FadeOutTargetVolume = 0;
	
	/*
	 * If true, the step ends when the AudioComponent finishes playing the sound.
	 * If false, the step ends inmediatly after playing the sound.
	 */
	UPROPERTY(EditAnywhere)
	bool bEndOnSoundFinish = false;

	UPROPERTY()
	FTimerHandle TimerHandle;
	
	UPROPERTY()
	UAudioComponent* AudioComponent;
};
