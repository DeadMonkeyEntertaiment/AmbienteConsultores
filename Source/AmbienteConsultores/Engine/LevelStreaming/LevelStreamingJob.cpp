#include "LevelStreamingJob.h"

#include "Kismet/GameplayStatics.h"

void ULevelStreamingJob::Begin()
{
	LoadNext();
}

void ULevelStreamingJob::Setup(TArray<TSoftObjectPtr<UWorld>> LevelsToProcess, bool IsLoadJob,
	bool VisibleAfterLoad, bool BlockOnLoad)
{
	LevelsLeft = LevelsToProcess;
	bIsLoadJob = IsLoadJob;
	bMakeVisibleAfterLoad = VisibleAfterLoad;
	bBlockOnLevelLoad = BlockOnLoad;
	
}

void ULevelStreamingJob::IBindOrCallToJobEnd_Implementation(const FOnLevelStreamingJobEnds& Delegate)
{
	if(bFinished)
	{
		Delegate.Execute(this);
		return;
	}
	JobEndedDelegates.Add(Delegate);
}

void ULevelStreamingJob::IUnbindFromJobEnd_Implementation(const FOnLevelStreamingJobEnds& Delegate)
{
	if(JobEndedDelegates.Contains(Delegate))
		JobEndedDelegates.Remove(Delegate);
}

void ULevelStreamingJob::LoadNext()
{
	if(LevelsLeft.IsEmpty())
	{
		BroadcastJobEnd();
		return;
	}
	const auto LevelToLoad = LevelsLeft.Pop();
	FLatentActionInfo LatentActionInfo;
	LatentActionInfo.CallbackTarget = this;
	LatentActionInfo.ExecutionFunction = "OnActionEnded";
	LatentActionInfo.UUID = 0;
	LatentActionInfo.Linkage = 0;
	if(bIsLoadJob)
		UGameplayStatics::LoadStreamLevelBySoftObjectPtr(GetWorld(), LevelToLoad,
			bMakeVisibleAfterLoad, bBlockOnLevelLoad, LatentActionInfo);
	else
		UGameplayStatics::UnloadStreamLevelBySoftObjectPtr(GetWorld(), LevelToLoad, LatentActionInfo,
			bBlockOnLevelLoad);
}

void ULevelStreamingJob::OnActionEnded()
{
	UE_LOG(LogLevel, Log, TEXT("[LoadStreamingProcess] Action ended."));
	LoadNext();
}

void ULevelStreamingJob::BroadcastJobEnd()
{
	bFinished = true;
	for ( int i = JobEndedDelegates.Num()-1; i >= 0; i--)
	{
		auto Delegate = JobEndedDelegates[i];
		if(Delegate.IsBound()) Delegate.Execute(this);
	}
	JobEndedDelegates.Empty();
}