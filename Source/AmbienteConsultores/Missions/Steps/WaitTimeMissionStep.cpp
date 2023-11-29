// Fill out your copyright notice in the Description page of Project Settings.


#include "WaitTimeMissionStep.h"

void UWaitTimeMissionStep::Execute(AActor* InPlayerActor)
{
	Super::Execute(InPlayerActor);

	if (!IsValid(PlayerActor)) return;
	TWeakObjectPtr<UWaitTimeMissionStep> ThisPtr= this;
	
	PlayerActor->GetWorld()->GetTimerManager().SetTimer(TimerHandle, [ThisPtr]()
	{
		if(ThisPtr.IsValid()) ThisPtr->EndExecution(true);
	}, TimeToWait, false);
}

void UWaitTimeMissionStep::Cancel()
{
	if (!IsValid(PlayerActor)) return;
	PlayerActor->GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	if (TimerHandle.IsValid())
	{
		TimerHandle.Invalidate();
	}
	Super::Cancel();
}

#if WITH_EDITOR
FText UWaitTimeMissionStep::GetNodeTitle() const
{
	return FText().FromString(Super::GetNodeTitle().ToString() + "["+FString::FromInt(TimeToWait) +"s]");
}
#endif
