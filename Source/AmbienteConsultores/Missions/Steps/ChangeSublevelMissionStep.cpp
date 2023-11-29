// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeSublevelMissionStep.h"

#include "AmbienteConsultores/Engine/LevelStreaming/LevelStreamingLoaderSubsystem.h"

void UChangeSublevelMissionStep::Execute(AActor* InPlayerActor)
{
	Super::Execute(InPlayerActor);
	bRevertAfterProcessEnds = false;
	if(LevelsToSwap.IsEmpty()) EndExecution(true);

	//Try change levels;
	ChangeLevel();
}

void UChangeSublevelMissionStep::Cancel()
{
	bRevertAfterProcessEnds = true;
	Super::Cancel();
}

void UChangeSublevelMissionStep::ChangeLevel(bool Reverse)
{
	const auto& LevelLoaderSubsystem = PlayerActor->GetWorld()->GetGameInstance()->GetSubsystem<ULevelStreamingLoaderSubsystem>();

	TScriptInterface<ILevelStreamingJobInterface> Job;
	
	// Should we do the inverse operation?
	if(bUnloadLevels || (!bUnloadLevels && Reverse))
		Job = LevelLoaderSubsystem->QueueUnloadStreamingLevels(LevelsToSwap, bLevelsBlockWhileChanging);
	else
		Job = LevelLoaderSubsystem->QueueLoadStreamingLevels(LevelsToSwap, bMakeLevelsVisibleAfterLoad, bLevelsBlockWhileChanging);
	
	FOnLevelStreamingJobEnds Delegate;
	Delegate.BindDynamic(this, &UChangeSublevelMissionStep::OnJobEnded);
	ILevelStreamingJobInterface::Execute_IBindOrCallToJobEnd(Job.GetObject(), Delegate);
}


void UChangeSublevelMissionStep::OnJobEnded(TScriptInterface<ILevelStreamingJobInterface> Reference)
{
	FOnLevelStreamingJobEnds Delegate;
	Delegate.BindDynamic(this, &UChangeSublevelMissionStep::OnJobEnded);
	ILevelStreamingJobInterface::Execute_IUnbindFromJobEnd(Reference.GetObject(), Delegate);
	// if this step was cancelled in the middle of the process, we need to revert it.
	if(bRevertAfterProcessEnds)
	{
		ChangeLevel(true);
		return;
	}
	EndExecution(true);
}
