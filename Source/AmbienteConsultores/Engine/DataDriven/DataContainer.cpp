// Fill out your copyright notice in the Description page of Project Settings.


#include "DataContainer.h"

void UDataContainer::IAddOrReplaceDataFragment_Implementation(UDataFragmentBase* Fragment)
{
	if(!IsValid(Fragment)) return;

	bool found = false;
	for (int i = 0; i < DataFragments.Num(); i++)
	{
		if(DataFragments[i].GetClass() == Fragment->GetClass())
		{
			DataFragments[i] = Fragment;
			found = true;
			break;
		}
	}
	if(!found)
	{
		DataFragments.Add(Fragment);
	}
}

UDataFragmentBase* UDataContainer::IGetDataFragmentByClass_Implementation(
	TSubclassOf<UDataFragmentBase> FragmentClass) const
{
	if (UClass* TargetClass = FragmentClass.Get())
		for (UDataFragmentBase* DataFragment : DataFragments)
			if(IsValid(DataFragment) && DataFragment->IsA(TargetClass)) return DataFragment; 
	return  {};
}
