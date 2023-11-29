// Fill out your copyright notice in the Description page of Project Settings.


#include "MissionSubsystem.h"

#include "MissionComponent.h"
#include "MissionDataContainer.h"
#include "AmbienteConsultores/Utils/AssetHelper.h"

void UMissionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	LoadMissionsFromAssets();
	Super::Initialize(Collection);
}

void UMissionSubsystem::UpdateEventState(FGameplayTag MissionTag, EMissionState NewState)
{
	if(!MissionsData.Contains(MissionTag)) return;

	MissionsData[MissionTag].MissionState = NewState;

	if(MissionsData[MissionTag].MissionState == MS_COMPLETED)
	{
		OnMissionCompleted.Broadcast(MissionTag);
		MissionsData[MissionTag].bRewardClaimed = true;
	}

	const auto& GameInstance = GetGameInstance();
}

TArray<FMissionData> UMissionSubsystem::GetEventStates()
{
	TArray<FMissionData> DataArray;
	if(!MissionsData.IsEmpty())
		MissionsData.GenerateValueArray(DataArray);
	return DataArray;
}

bool UMissionSubsystem::GetMissionState(FGameplayTag MissionTag, FMissionData& MissionData)
{
	if(!MissionsData.Contains(MissionTag)) return false;

	MissionData = MissionsData[MissionTag];
	
	return true;
}

void UMissionSubsystem::UpdateMissionsList(TArray<FMissionData> Missions)
{
	for (auto& Mission : MissionsData)
	{
		Mission.Value.MissionState = MS_UNDISCOVERED;
	}

	for (auto Event : Missions)
	{
		MissionsData.Add(Event.MissionTag, Event);
	}

	OnMissionListUpdated.Broadcast();
}

void UMissionSubsystem::LoadMissionsFromAssets()
{
	if (RawDataAssets.IsEmpty())
	{
		RawDataAssets = UAssetHelper::LoadAssetsFromClass(UMissionDataContainer::StaticClass());
	}

	for(UObject* Asset : RawDataAssets)
	{
		const UMissionDataContainer* AscensionDataContainer = static_cast<UMissionDataContainer*>(Asset);
		UMissionDataFragment* AscensionDataFragment = AscensionDataContainer->GetDataFragmentByClass<UMissionDataFragment>();

		if(!MissionsData.Contains(AscensionDataFragment->MissionTag))
		{
			FMissionData AscensionEventData;
			AscensionEventData.MissionState = AscensionDataFragment->StartingMissionState;
			AscensionEventData.MissionTag = AscensionDataFragment->MissionTag;
			AscensionEventData.DataFragmentRef = AscensionDataFragment;
			MissionsData.Add(AscensionEventData.MissionTag, AscensionEventData);
		}
	}
}
