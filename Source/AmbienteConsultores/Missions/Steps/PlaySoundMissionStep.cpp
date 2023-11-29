// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaySoundMissionStep.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

void UPlaySoundMissionStep::Execute(AActor* InPlayerActor)
{
	Super::Execute(InPlayerActor);
	AudioComponent = UGameplayStatics::CreateSound2D(PlayerActor->GetWorld(), Sound);
	if(bEndOnSoundFinish)
	{
		AudioComponent->OnAudioFinished.AddDynamic(this, &ThisClass::OnAudioFinished);
		AudioComponent->Play();
	}
	else
	{
		AudioComponent->Play();
		EndExecution(true);
	}
	if(StopAfterSeconds > 0)
	{
		TWeakObjectPtr<ThisClass> ThisPtr = this;
		InPlayerActor->GetWorld()->GetGameInstance()->GetTimerManager().SetTimer(TimerHandle,
			[ThisPtr]()
			{
				if(ThisPtr.IsValid() && IsValid(ThisPtr->AudioComponent) && ThisPtr->AudioComponent->IsPlaying())
				{
					ThisPtr->StopSound();
					if(!ThisPtr->bEndOnSoundFinish) ThisPtr->EndExecution(true);
				}
			}, StopAfterSeconds, false);
	}
}

void UPlaySoundMissionStep::Cancel()
{
	StopSound(true);
	Super::Cancel();
}

void UPlaySoundMissionStep::OnAudioFinished()
{
	if(IsValid(AudioComponent))
		AudioComponent->DestroyComponent();

	PlayerActor->GetGameInstance()->GetTimerManager().ClearTimer(TimerHandle);
	
	EndExecution(true);
}

void UPlaySoundMissionStep::StopSound(bool bShouldDestroyComponent)
{
	if(IsValid(AudioComponent) && AudioComponent->IsPlaying())
	{
		AudioComponent->FadeOut(FadeOutDuration, FadeOutTargetVolume);
		if(bShouldDestroyComponent) AudioComponent->DestroyComponent();
	}
}

