// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataContainerInterface.h"
#include "DataFragmentBase.h"
#include "DataContainer.generated.h"

/**
 * Class container of data-fragments.
 */
UCLASS(ClassGroup="Data", Blueprintable, BlueprintType)
class UDataContainer : public UPrimaryDataAsset, public IDataContainerInterface
{
	GENERATED_BODY()

public:

	/**
	 * Adds a datafragment(or replaces it if it's already added) at runtime.
	 */
	virtual void IAddOrReplaceDataFragment_Implementation(UDataFragmentBase* Fragment) override;
	
	/**
	 * Returns the Data-fragment of "FragmentClass" passed by parameter if found. Nullptr otherwise.
	 */
	virtual UDataFragmentBase* IGetDataFragmentByClass_Implementation(
		TSubclassOf<UDataFragmentBase> FragmentClass) const override;

	
	template<class T>
	T* GetDataFragmentByClass() const;
protected:
	/**
	 * Data-fragments list for this container.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="DataDriven", Instanced)
	TArray<TObjectPtr<UDataFragmentBase>> DataFragments;
};

template <class T>
T* UDataContainer::GetDataFragmentByClass() const
{
	if (UClass* TargetClass = T::StaticClass())
		for (UDataFragmentBase* DataFragment : DataFragments)
			if(IsValid(DataFragment) && DataFragment->IsA(TargetClass)) return CastChecked<T>(DataFragment); 
	return  {};
}
