// Fill out your copyright notice in the Description page of Project Settings.


#include "ModifyAudioComponentMissionStep.h"

#include "Components/AudioComponent.h"


void UModifyAudioComponentMissionStep::Execute(AActor* InPlayerActor)
{
	Super::Execute(InPlayerActor);

	if(!ensureMsgf(!AudioComponentOwner.IsNull(), TEXT("AudioComponent's owner not set.")))
	{
		EndExecution(false);
		return;
	}

	const auto& AudioComponent = AudioComponentOwner->FindComponentByClass<UAudioComponent>();
	if(!ensureMsgf(IsValid(AudioComponent), TEXT("[%s]AudioComponent not found in Target actor."), *ThisClass::GetName()))
	{
		EndExecution(false);
		return;
	}

	AudioComponent->SetPitchMultiplier(NewPitchMultiplier);
	AudioComponent->SetVolumeMultiplier(NewVolumeMultiplier);
	AudioComponent->AdjustAttenuation(NewAttenuationSettings);
	AudioComponent->SetSound(NewSound);
	if(!AudioComponent->IsPlaying()) AudioComponent->Play();
	EndExecution(true);
}
