// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataContainer.h"
#include "Components/ActorComponent.h"
#include "AmbienteConsultores/Utils/UtilityBlueprintFunctionLibrary.h"
#include "DataDrivenComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDataContainerUpdated, UDataContainer*, UpdatedDataContainer);

class UDataFragmentBase;
UCLASS(ClassGroup=(DataDriven), meta=(BlueprintSpawnableComponent))
class UDataDrivenComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDataDrivenComponent();
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UDataContainer* GetDataContainer();
	
	UFUNCTION(BlueprintCallable) void SetDataContainer(UDataContainer* NewContainer);

	UFUNCTION(BlueprintCallable) void AddOrReplaceDataFragmentsInContainer(TArray<UDataFragmentBase*> DataFragments);
	UFUNCTION(BlueprintCallable) void AddOrReplaceDataFragmentInContainer(UDataFragmentBase* DataFragments, bool BroadcastChanges = true);

	/**
	 * @brief Returns the Data-fragment of "FragmentClass" passed by parameter if found. Nullptr otherwise
	 * @param FragmentClass UDataFragmentBase child class we are looking in the Data Container
	 * @return Data-fragment
	 */
	template<class T>
	T* GetValidatedDataFragmentByClass(TSubclassOf<UDataFragmentBase> FragmentClass = T::StaticClass());

	/**
	 * @brief Returns the Data-fragment of "FragmentClass" passed by parameter if found. Nullptr otherwise 
	 * @param FragmentClass UDataFragmentBase child class we are looking in the Data Container
	 * @param Outcome Whether is valid or not the DataFragment requested
	 * @return Data-fragment
	 */
	UFUNCTION(BlueprintCallable,
		meta=(DisplayName = "Get Validated Data Fragment By Class", DeterminesOutputType = "FragmentClass",
			ExpandEnumAsExecs = "Outcome"))
	UDataFragmentBase* BP_GetValidatedDataFragmentByClass(TSubclassOf<UDataFragmentBase> FragmentClass,
	                                                      TEnumAsByte<EValidationPins>& Outcome);

	UPROPERTY(BlueprintAssignable) FDataContainerUpdated OnDataContainerUpdated;
	
private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UDataContainer> Container;

	UPROPERTY() TObjectPtr<UDataContainer> VirtualContainer;
};

template <class T>
T* UDataDrivenComponent::GetValidatedDataFragmentByClass(TSubclassOf<UDataFragmentBase> FragmentClass)
{
	ensureMsgf(IsValid(GetDataContainer()), TEXT("The class %s doesn't have a data container"), *GetOwner()->GetName());
	if (!IsValid(GetDataContainer())) return nullptr;

	ensureMsgf(IsValid(FragmentClass), TEXT("Given DataFragmentClass is not valid."));

	UDataFragmentBase* DataFragment = IDataContainerInterface::Execute_IGetDataFragmentByClass(GetDataContainer(), FragmentClass);
	if (!IsValid(DataFragment)) return nullptr;
	
	return CastChecked<T>(DataFragment);
}
