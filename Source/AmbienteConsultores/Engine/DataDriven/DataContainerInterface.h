// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DataContainerInterface.generated.h"

class UDataFragmentBase;
UINTERFACE()
class UDataContainerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class IDataContainerInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Data",
		meta = (DisplayName="GetDataFragmentByClass", DeterminesOutputType = "FragmentClass"))
	UDataFragmentBase* IGetDataFragmentByClass(TSubclassOf<UDataFragmentBase> FragmentClass) const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Data", meta=(DisplayName="AddOrReplaceDataFragment"))
	void IAddOrReplaceDataFragment(UDataFragmentBase* Fragment);
};
