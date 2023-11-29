// Fill out your copyright notice in the Description page of Project Settings.


#include "DataDrivenHelper.h"

#include "DataContainer.h"
#include "DataDrivenComponent.h"

UDataContainer* UDataDrivenHelper::GetDataContainer(AActor* Target)
{
	ensureMsgf(IsValid(Target), TEXT("Invalid target."));
	if(IsValid(Target))
	{
		UDataDrivenComponent* DataDrivenComponent = Target->FindComponentByClass<UDataDrivenComponent>();
		ensureMsgf(IsValid(DataDrivenComponent), TEXT("Datadriven component not found in '%s'"), *Target->GetName());
		ensureMsgf(IsValid(DataDrivenComponent->GetDataContainer()), TEXT("Datacontainer not found in '%s'"), *Target->GetName());
		if(IsValid(DataDrivenComponent) && IsValid(DataDrivenComponent->GetDataContainer()))
		{
			return DataDrivenComponent->GetDataContainer();
		}
	}
	return nullptr;
}
