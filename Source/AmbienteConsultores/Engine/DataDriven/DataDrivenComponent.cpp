// Fill out your copyright notice in the Description page of Project Settings.


#include "DataDrivenComponent.h"

#include "AmbienteConsultores/Utils/UtilityBlueprintFunctionLibrary.h"


UDataDrivenComponent::UDataDrivenComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDataDrivenComponent::BeginPlay()
{
	Super::BeginPlay();
}

UDataContainer* UDataDrivenComponent::GetDataContainer()
{
	if(!IsValid(VirtualContainer))
	{
		VirtualContainer = DuplicateObject<UDataContainer>(Container, this);
	}
	return VirtualContainer;
}

void UDataDrivenComponent::SetDataContainer(UDataContainer* NewContainer)
{
	VirtualContainer = DuplicateObject<UDataContainer>(NewContainer, this);
	OnDataContainerUpdated.Broadcast(VirtualContainer);
}

void UDataDrivenComponent::AddOrReplaceDataFragmentInContainer(UDataFragmentBase* DataFragment, bool BroadcastChanges)
{
	IDataContainerInterface::Execute_IAddOrReplaceDataFragment(GetDataContainer(), DataFragment);
	if(BroadcastChanges) OnDataContainerUpdated.Broadcast(GetDataContainer());
}

void UDataDrivenComponent::AddOrReplaceDataFragmentsInContainer(TArray<UDataFragmentBase*> DataFragments)
{
	for (auto Fragment : DataFragments)
	{
		AddOrReplaceDataFragmentInContainer(Fragment, false);
	}
	OnDataContainerUpdated.Broadcast(GetDataContainer());
}

UDataFragmentBase* UDataDrivenComponent::BP_GetValidatedDataFragmentByClass(
	TSubclassOf<UDataFragmentBase> FragmentClass, TEnumAsByte<EValidationPins>& Outcome)
{
	UDataFragmentBase* DataFragment = GetValidatedDataFragmentByClass<UDataFragmentBase>(FragmentClass);
	Outcome =  IsValid(DataFragment)
		? EValidationPins::Valid
		: EValidationPins::NotValid;
	
	return DataFragment;
}
