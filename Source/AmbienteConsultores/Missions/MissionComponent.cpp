// Fill out your copyright notice in the Description page of Project Settings.


#include "MissionComponent.h"

#include "MissionSubsystem.h"
#include "LevelSequence.h"
#include "MissionLog.h"
#include "Components/AudioComponent.h"
#include "AmbienteConsultores/Engine/DataDriven/DataDrivenComponent.h"
#include "AmbienteConsultores/Engine/LevelStreaming/LevelStreamingJobInterface.h"
#include "AmbienteConsultores/Engine/LevelStreaming/LevelStreamingLoaderSubsystem.h"
#include "AmbienteConsultores/Engine/Sequences/SequenceSubsystem.h"
#include "AmbienteConsultores/Entities/TriggerActorInterface.h"
#include "Kismet/GameplayStatics.h"


UMissionComponent::UMissionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	State = MS_UNDISCOVERED;
}

void UMissionComponent::OnMissionsListUpdated()
{
	FTriggerInteractionEvent StartEvent;
	StartEvent.BindDynamic(this, &UMissionComponent::OnStartTriggerActivated);

	ITriggerActorInterface::Execute_IUnbindFromTriggerInteraction(DataFragmentRef->StartTrigger.Get(), StartEvent);

	LoadMissionStates();
	UpdateMap();

	if (State == MS_COMPLETED) return;

	ITriggerActorInterface::Execute_IBindToTriggerInteraction(DataFragmentRef->StartTrigger.Get(), StartEvent);
}

void UMissionComponent::LoadMissionStates()
{
	const auto& AscensionEventSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMissionSubsystem>();
	check(AscensionEventSubsystem);

	FMissionData AscensionEventData;
	if (AscensionEventSubsystem->GetMissionState(DataFragmentRef->MissionTag, AscensionEventData))
	{
		State = AscensionEventData.MissionState;
	}
}

void UMissionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	const auto& AscensionEventSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMissionSubsystem>();
	check(AscensionEventSubsystem);
	AscensionEventSubsystem->OnMissionListUpdated.RemoveDynamic(this, &ThisClass::OnMissionsListUpdated);

	if (bIsMissionActive)
		EndMission(false);

	if (IsValid(DataFragmentRef) && IsValid(DataFragmentRef->StartTrigger.Get()))
	{
		FTriggerInteractionEvent StartEvent;
		StartEvent.BindDynamic(this, &UMissionComponent::OnStartTriggerActivated);
		ITriggerActorInterface::Execute_IUnbindFromTriggerInteraction(DataFragmentRef->StartTrigger.Get(), StartEvent);
	}

	if (IsValid(Executor))
		Executor->OnExecutionFinished.RemoveDynamic(this, &UMissionComponent::OnExecutionDone);

	Super::EndPlay(EndPlayReason);
	if(IsValid(Executor)) Executor->ConditionalBeginDestroy();
}

void UMissionComponent::BeginPlay()
{
	Super::BeginPlay();

	//Check all required config
	const auto& DataDrivenComponent = GetOwner()->FindComponentByClass<UDataDrivenComponent>();
	if (!ensureMsgf(DataDrivenComponent, TEXT("Datadriven component not found in owner [%s]"),
	                *GetOwner()->GetName())) return;

	UDataContainer* Container = DataDrivenComponent->GetDataContainer();
	if (!ensureMsgf(Container, TEXT("Container is not valid"))) return;

	DataFragmentRef = DataDrivenComponent->GetValidatedDataFragmentByClass<UMissionDataFragment>();
	if (!ensureMsgf(DataFragmentRef, TEXT("Mission data fragment not set to '%s' container."),
	                *Container->GetName())) return;

	ensureMsgf(DataFragmentRef->StartTrigger.Get(),
	           TEXT("Start Trigger not set in mission data fragment from container '%s'."),
	           *Container->GetName());
	ensureMsgf(DataFragmentRef->MissionGraph,
	           TEXT("Mission graph not set in mission data fragment from container '%s'."),
	           *Container->GetName());
#if WITH_EDITOR
	check(DataFragmentRef->MissionGraph)
	UE_LOG(LogMission, Log, TEXT("%s"), *DataFragmentRef->MissionGraph->ToString());
#endif

	Executor = NewObject<UMissionExecutor>(this);
	const auto& AscensionEventSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMissionSubsystem>();
	check(AscensionEventSubsystem);
	AscensionEventSubsystem->OnMissionListUpdated.AddDynamic(this, &ThisClass::OnMissionsListUpdated);

	OnMissionsListUpdated();
}

void UMissionComponent::OnStartTriggerActivated(FTriggerInteractionInfo Info)
{
	if (Info.bIsInteractionActive)
	{
		PlayerCharacter = Info.Instigator;
		PrepareMission();
	}
}

void UMissionComponent::PrepareMission()
{
	if (bIsMissionActive) return;

	if (IsValid(DataFragmentRef->EndTrigger.Get()))
	{
		FTriggerInteractionEvent EndEvent;
		EndEvent.BindDynamic(this, &UMissionComponent::OnEndTriggerActivated);
		ITriggerActorInterface::Execute_IBindToTriggerInteraction(DataFragmentRef->EndTrigger.Get(), EndEvent);
	}
	bIsMissionActive = true;
	UE_LOG(LogMission, Log, TEXT("Preparing event '%s'."), *GetClass()->GetName());
	if (State == MS_UNDISCOVERED)
	{
		State = MS_DISCOVERED;
		const auto& AscensionEventSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMissionSubsystem>();
		AscensionEventSubsystem->UpdateEventState(DataFragmentRef->MissionTag, State);

		bIsExecutingIntroSequence = PlaySequence(DataFragmentRef->IntroSequence);
		if (!bIsExecutingIntroSequence) StartMission();
	}
	else
	{
		StartMission();
	}
}

void UMissionComponent::StartMission()
{
	UE_LOG(LogMission, Log, TEXT("Starting event '%s'."), *GetClass()->GetName());
	if (DataFragmentRef->bIsBlockerEvent)
		UpdateBlocking(true);
	if (IsValid(DataFragmentRef->StartSFX)) UGameplayStatics::PlaySound2D(GetWorld(), DataFragmentRef->StartSFX);

	if (IsValid(DataFragmentRef->MissionMusic))
	{
		CurrentAudioComponent = UGameplayStatics::CreateSound2D(GetWorld(), DataFragmentRef->MissionMusic);
		if (CurrentAudioComponent) CurrentAudioComponent->Play();
	}

	OnMissionStarted.Broadcast(GetOwner());

	ensure(IsValid(Executor));
	Executor->OnExecutionFinished.AddDynamic(this, &UMissionComponent::OnExecutionDone);
	Executor->StartGraphExecution(PlayerCharacter, DataFragmentRef->MissionGraph.Get());
}

void UMissionComponent::GiveReward()
{
	FMissionData AscensionEventData;
	const auto& AscensionEventSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMissionSubsystem>();
	AscensionEventSubsystem->GetMissionState(DataFragmentRef->MissionTag, AscensionEventData);

	if (AscensionEventData.bRewardClaimed) return;

	if (!DataFragmentRef->RewardClass.IsEmpty())
	{
		for (auto RewardClass : DataFragmentRef->RewardClass)
		{
			RewardClass->Claim(PlayerCharacter);
		}
	}
}

void UMissionComponent::OnEndTriggerActivated(FTriggerInteractionInfo Info)
{
	if (!Info.bIsInteractionActive && bIsMissionActive)
		Executor->CancelExecution();
}

void UMissionComponent::EndMission(bool Completed)
{
	bIsMissionActive = false;
	Executor->OnExecutionFinished.RemoveDynamic(this, &UMissionComponent::OnExecutionDone);
	UE_LOG(LogMission, Log, TEXT("Ending event '%s'.(Success: %d)"), *GetClass()->GetName(), Completed);
	if (Completed)
	{
		if (IsValid(DataFragmentRef->EndSFX)) UGameplayStatics::PlaySound2D(GetWorld(), DataFragmentRef->EndSFX);
		if (CurrentAudioComponent && CurrentAudioComponent->IsPlaying()) CurrentAudioComponent->Stop();
		//Unbind from trigger.
		FTriggerInteractionEvent StartEvent;
		StartEvent.BindDynamic(this, &UMissionComponent::OnStartTriggerActivated);
		ITriggerActorInterface::Execute_IUnbindFromTriggerInteraction(DataFragmentRef->StartTrigger.Get(), StartEvent);

		State = MS_COMPLETED;

		//Update map
		if (DataFragmentRef->ApplyLevelChangesOnCompleted) UpdateMap();
		//Give reward
		GiveReward();
		const auto& AscensionEventSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMissionSubsystem>();
		AscensionEventSubsystem->UpdateEventState(DataFragmentRef->MissionTag, State);
	}
	UpdateBlocking(false);
	PlayerCharacter = nullptr;
	if (IsValid(DataFragmentRef->EndTrigger.Get()))
	{
		FTriggerInteractionEvent EndEvent;
		EndEvent.BindDynamic(this, &UMissionComponent::OnEndTriggerActivated);
		ITriggerActorInterface::Execute_IUnbindFromTriggerInteraction(DataFragmentRef->EndTrigger.Get(), EndEvent);
	}
	if (OnMissionEnded.IsBound()) OnMissionEnded.Broadcast(GetOwner(), Completed);
	CheckChangeLevel();
}

void UMissionComponent::CheckChangeLevel()
{
	if (State == MS_COMPLETED && DataFragmentRef->LevelToLoad.IsPending())
	{
		const auto& LevelLoaderSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<ULevelStreamingLoaderSubsystem>();
		//Change Levels
		LevelLoaderSubsystem->QueueLoadStreamingLevel(DataFragmentRef->LevelToLoad, true, true);
	}
}

void UMissionComponent::UpdateMap()
{
	UE_LOG(LogMission, Log, TEXT("Updating map for event '%s'.(Completed: %d)"), *GetClass()->GetName(),
	       State == MS_COMPLETED);
	const auto& LevelLoaderSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<ULevelStreamingLoaderSubsystem>();
	if (State == MS_COMPLETED)
	{
		if (DataFragmentRef->LevelsToActivate.IsEmpty())
		{
			OnSublevelsActivated(nullptr);
			return;
		}

		auto LoadJob = LevelLoaderSubsystem->QueueLoadStreamingLevels(DataFragmentRef->LevelsToActivate, true, true);

		FOnLevelStreamingJobEnds Delegate;
		Delegate.BindDynamic(this, &UMissionComponent::OnSublevelsActivated);
		ILevelStreamingJobInterface::Execute_IBindOrCallToJobEnd(LoadJob.GetObject(), Delegate);
	}
	else
	{
		if (DataFragmentRef->LevelsToDeactivate.IsEmpty())
		{
			OnSublevelsReverted(nullptr);
			return;
		}
		//Unload activated levels
		auto UnloadJob = LevelLoaderSubsystem->QueueUnloadStreamingLevels(DataFragmentRef->LevelsToActivate, true);
		FOnLevelStreamingJobEnds Delegate;
		Delegate.BindDynamic(this, &UMissionComponent::OnSublevelsReverted);
		ILevelStreamingJobInterface::Execute_IBindOrCallToJobEnd(UnloadJob.GetObject(), Delegate);
	}
}

void UMissionComponent::OnSublevelsActivated(TScriptInterface<ILevelStreamingJobInterface> JobReference)
{
	//Unbind from old job
	if (IsValid(JobReference.GetObject()))
	{
		FOnLevelStreamingJobEnds OldDelegate;
		OldDelegate.BindDynamic(this, &UMissionComponent::OnSublevelsActivated);
		ILevelStreamingJobInterface::Execute_IUnbindFromJobEnd(JobReference.GetObject(), OldDelegate);
	}

	const auto& LevelLoaderSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<ULevelStreamingLoaderSubsystem>();
	auto LoadJob = LevelLoaderSubsystem->QueueUnloadStreamingLevels(DataFragmentRef->LevelsToDeactivate, true);

	//Bind to new job
	FOnLevelStreamingJobEnds Delegate;
	Delegate.BindDynamic(this, &UMissionComponent::OnSublevelsDeactivated);
	ILevelStreamingJobInterface::Execute_IBindOrCallToJobEnd(LoadJob.GetObject(), Delegate);
}

void UMissionComponent::OnSublevelsDeactivated(TScriptInterface<ILevelStreamingJobInterface> JobReference)
{
	//Unbind from old job
	FOnLevelStreamingJobEnds OldDelegate;
	OldDelegate.BindDynamic(this, &UMissionComponent::OnSublevelsDeactivated);
	ILevelStreamingJobInterface::Execute_IUnbindFromJobEnd(JobReference.GetObject(), OldDelegate);
}


void UMissionComponent::OnSublevelsReverted(TScriptInterface<ILevelStreamingJobInterface> JobReference)
{
	if (IsValid(JobReference.GetObject()))
	{
		FOnLevelStreamingJobEnds OldDelegate;
		OldDelegate.BindDynamic(this, &UMissionComponent::OnSublevelsActivated);
		ILevelStreamingJobInterface::Execute_IUnbindFromJobEnd(JobReference.GetObject(), OldDelegate);
	}

	const auto& LevelLoaderSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<ULevelStreamingLoaderSubsystem>();
	LevelLoaderSubsystem->QueueLoadStreamingLevels(DataFragmentRef->LevelsToDeactivate, true, true);
}

void UMissionComponent::OnExecutionDone(bool Completed)
{
	if (Completed)
	{
		if (IsValid(DataFragmentRef->OutroSequence)) PlaySequence(DataFragmentRef->OutroSequence);
		else EndMission(true);
	}
	else
	{
		EndMission(false);
	}
}

bool UMissionComponent::PlaySequence(ULevelSequence* Sequence, bool bBlockDefaultSkipPrompt)
{
	if (!IsValid(Sequence)) return false;
	UE_LOG(LogMission, Log, TEXT("Playing sequence '%s' for event '%s'."), *Sequence->GetName(),
	       *GetClass()->GetName());

	FFinishedCutsceneDelegate Delegate;
	Delegate.BindDynamic(this, &UMissionComponent::OnSequenceFinished);
	GetWorld()->GetGameInstance()->GetSubsystem<USequenceSubsystem>()->PlayOrderedCutscene(Sequence, Delegate);

	return true;
}

void UMissionComponent::OnSequenceFinished()
{
	if (bIsExecutingIntroSequence)
	{
		UE_LOG(LogMission, Log, TEXT("Intro sequece finished for event '%s'."), *GetClass()->GetName());
		//Intro sequence finished.
		bIsExecutingIntroSequence = false;
		State = MS_DISCOVERED;
		
		StartMission();
	}
	else
	{
		UE_LOG(LogMission, Log, TEXT("Outro sequece finished for event '%s'."), *GetClass()->GetName());
		//Outro sequence finished.
		EndMission(true);
	}
}

void UMissionComponent::SetState(EMissionState NewState)
{
	State = NewState;
}


void UMissionComponent::UpdateBlocking(bool Activate)
{
	UE_LOG(LogMission, Log, TEXT("Updating blocking actors for event '%s'."), *GetClass()->GetName());
	for (auto Blocking : DataFragmentRef->BlockingActors)
	{
		if (!Blocking.IsValid()) continue;
		Blocking->SetActorHiddenInGame(!Activate);
		Blocking->SetActorEnableCollision(Activate);
	}
}
