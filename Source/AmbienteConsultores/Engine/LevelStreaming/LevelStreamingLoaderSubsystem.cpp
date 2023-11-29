// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelStreamingLoaderSubsystem.h"

#include "Kismet/GameplayStatics.h"

void ULevelStreamingLoaderSubsystem::ExecuteJob()
{
	if(IsProcessRunning() || JobsQueue.IsEmpty()) return;

	ActiveJob = JobsQueue[0];
	FOnLevelStreamingJobEnds OnJobEndDelegate;
	OnJobEndDelegate.BindDynamic(this, &ULevelStreamingLoaderSubsystem::OnJobEnd);
	ILevelStreamingJobInterface::Execute_IBindOrCallToJobEnd(ActiveJob, OnJobEndDelegate);
	JobsQueue.RemoveAt(0);
	ActiveJob->Begin();
}

void ULevelStreamingLoaderSubsystem::OnJobEnd(TScriptInterface<ILevelStreamingJobInterface> JobReference)
{
	FOnLevelStreamingJobEnds OldDelegate;
	OldDelegate.BindDynamic(this, &ULevelStreamingLoaderSubsystem::OnJobEnd);
	ILevelStreamingJobInterface::Execute_IUnbindFromJobEnd(JobReference.GetObject(), OldDelegate);
	ActiveJob = nullptr;
	ExecuteJob();
}


TScriptInterface<ILevelStreamingJobInterface> ULevelStreamingLoaderSubsystem::QueueLoadStreamingLevel(TSoftObjectPtr<UWorld> Level,
	bool bVisibleAfterLoading, bool bBlockOnLoad)
{
	auto NewJob = NewObject<ULevelStreamingJob>(this);
	TArray<TSoftObjectPtr<UWorld>> PendingJobs;
	PendingJobs.Add(Level);
	NewJob->Setup(PendingJobs, true, bVisibleAfterLoading, bBlockOnLoad);
	JobsQueue.Push(NewJob);
	ExecuteJob();
	return NewJob;
}


TScriptInterface<ILevelStreamingJobInterface> ULevelStreamingLoaderSubsystem::QueueUnloadStreamingLevel(TSoftObjectPtr<UWorld> Level,
	bool bBlockOnLoad)
{
	auto NewJob = NewObject<ULevelStreamingJob>(this);
	TArray<TSoftObjectPtr<UWorld>> PendingJobs;
	PendingJobs.Add(Level);
	NewJob->Setup(PendingJobs, false, false, bBlockOnLoad);
	JobsQueue.Push(NewJob);
	ExecuteJob();
	return NewJob;
}

TScriptInterface<ILevelStreamingJobInterface> ULevelStreamingLoaderSubsystem::QueueLoadStreamingLevels(TArray<TSoftObjectPtr<UWorld>> Levels,
	bool bVisibleAfterLoading, bool bBlockOnLoad)
{
	auto NewJob = NewObject<ULevelStreamingJob>(this);
	NewJob->Setup(Levels, true, bVisibleAfterLoading, bBlockOnLoad);
	JobsQueue.Push(NewJob);
	ExecuteJob();
	return NewJob;
}

TScriptInterface<ILevelStreamingJobInterface> ULevelStreamingLoaderSubsystem::QueueUnloadStreamingLevels(TArray<TSoftObjectPtr<UWorld>> Levels,
	bool bBlockOnLoad)
{
	auto NewJob = NewObject<ULevelStreamingJob>(this);
	NewJob->Setup(Levels, false, false, bBlockOnLoad);
	JobsQueue.Push(NewJob);
	ExecuteJob();
	return NewJob;
}