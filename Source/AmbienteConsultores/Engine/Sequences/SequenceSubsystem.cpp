// Fill out your copyright notice in the Description page of Project Settings.


#include "SequenceSubsystem.h"

#include "AmbienteConsultores/Engine/WorldRegistry/WorldRegistrySubsystem.h"

USequenceSubsystem::USequenceSubsystem()
{
}

void USequenceSubsystem::SkipCutscene()
{
	if (!IsValid(MainSequencePlayer) || !MainSequencePlayer->IsPlaying()) return;

	FMovieSceneSequencePlaybackParams PlaybackParams;
	PlaybackParams.PositionType = EMovieScenePositionType::Time;
	PlaybackParams.UpdateMethod = EUpdatePositionMethod::Play;
	PlaybackParams.Time = MainSequencePlayer->GetEndTime().AsSeconds();

	MainSequencePlayer->SetPlaybackPosition(PlaybackParams);
}

void USequenceSubsystem::PlayCutscene(ULevelSequence* Sequence, FMovieSceneSequencePlaybackSettings PlaybackSettings)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.ObjectFlags |= RF_Transient;
	SpawnParams.bAllowDuringConstructionScript = true;
	SpawnParams.bDeferConstruction = true;

	ALevelSequenceActor* LSActor;
	MainSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), Sequence, PlaybackSettings, LSActor);
	MainSequencePlayer->OnFinished.AddDynamic(this, &USequenceSubsystem::OnSequenceFinished);
	MainSequencePlayer->Play();

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	// UControllerMovementComponent* MovementController = PC->FindComponentByClass<UControllerMovementComponent>();
	// if (IsValid(MovementController)) MovementController->EndMove();
	PC->GetPawn()->SetActorHiddenInGame(true);
	PC->GetPawn()->CustomTimeDilation = 0.0f;

	if (const UWorldRegistrySubsystem* Registry = PC->GetPawn()->GetWorld()->GetSubsystem<UWorldRegistrySubsystem>())
	{
		TArray<AActor*> RegisteredActors = Registry->GetWorldRegistry()->GetAllRegisteredActors();
		for (AActor* Actor : RegisteredActors)
		{
			if(!IsValid(Actor)) continue;
			Actor->SetActorHiddenInGame(true); 
			Actor->CustomTimeDilation = 0.0f;
		}
	}
}

void USequenceSubsystem::PlayOrderedCutscene(ULevelSequence* Sequence, const FFinishedCutsceneDelegate& OnFinishedDelegate, FMovieSceneSequencePlaybackSettings PlaybackSettings)
{
	if (!IsValid(Sequence)) return;
	DelegateMap.Add(Sequence->GetName(), OnFinishedDelegate);
	PlayOrderedCutscene(Sequence, PlaybackSettings);
}

void USequenceSubsystem::PlayOrderedCutscene(ULevelSequence* Sequence, FMovieSceneSequencePlaybackSettings PlaybackSettings)
{
	if (!IsValid(Sequence)) return;

	if (IsValid(MainSequencePlayer) && MainSequencePlayer->IsPlaying())
	{
		SequenceQueue.Push(Sequence);
		PlaybackSettingsMap.Add(Sequence->GetName(), PlaybackSettings);
		return;
	}

	PlayCutscene(Sequence, PlaybackSettings);
}

void USequenceSubsystem::OnSequenceFinished()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	PC->GetPawn()->SetActorHiddenInGame(false);
	PC->GetPawn()->CustomTimeDilation = 1.0f;

	if (const UWorldRegistrySubsystem* Registry = PC->GetPawn()->GetWorld()->GetSubsystem<UWorldRegistrySubsystem>())
	{
		TArray<AActor*> RegisteredActors = Registry->GetWorldRegistry()->GetAllRegisteredActors();
		for (AActor* Actor : RegisteredActors) 
		{
			if(!IsValid(Actor)) continue;
			Actor->SetActorHiddenInGame(false);
			Actor->CustomTimeDilation = 1.0f;
		}
	}

	// Remove delegates and residuals
	MainSequencePlayer->OnFinished.RemoveDynamic(this, &USequenceSubsystem::OnSequenceFinished);

	if (DelegateMap.Contains(MainSequencePlayer->GetSequenceName()))
		DelegateMap.FindAndRemoveChecked(MainSequencePlayer->GetSequenceName()).ExecuteIfBound();
	
	if (PlaybackSettingsMap.Contains(MainSequencePlayer->GetSequenceName()))
		PlaybackSettingsMap.FindAndRemoveChecked(MainSequencePlayer->GetSequenceName());
	
	// Check for next sequence
	if (SequenceQueue.Num() == 0) return;

	ULevelSequence* NextSequence = SequenceQueue.Pop(true);
	FString SequenceName = NextSequence->GetName();

	if (PlaybackSettingsMap.Contains(SequenceName))
	{
		PlayOrderedCutscene(NextSequence, PlaybackSettingsMap[SequenceName]);
		return;
	}
	
	PlayOrderedCutscene(NextSequence);
}