// Fill out your copyright notice in the Description page of Project Settings.


#include "MissionStepBase.h"

#include "AmbienteConsultores/Missions/MissionLog.h"

void UMissionStepBase::Execute(AActor* InPlayerActor)
{
	PlayerActor = InPlayerActor;
	UE_LOG(LogMission, Log, TEXT("Step '%s' started"), *GetClass()->GetName());
}

void UMissionStepBase::Cancel()
{
	UE_LOG(LogMission, Log, TEXT("Step '%s' cancelled."), *GetClass()->GetName());
	EndExecution(false);
}

FString UMissionStepBase::ToString()
{
	return GetClass()->GetName();
}

void UMissionStepBase::EndExecution(bool bSuccess)
{
	UE_LOG(LogMission, Log, TEXT("Step '%s' ended execution (success: %d)"), *GetClass()->GetName(), bSuccess);
	if(OnStepDone.IsBound()) OnStepDone.Broadcast(this, bSuccess);
}
