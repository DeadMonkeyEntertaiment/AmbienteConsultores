
#pragma once

#include "CoreMinimal.h"
#include "AmbienteConsultores/Utils/BaseTickableObject.h"
#include "ProtectionStrategy.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPutOn);
DECLARE_DYNAMIC_DELEGATE(FOnPutOnInternal);

UCLASS(Blueprintable, BlueprintType, EditInlineNew)
class AMBIENTECONSULTORES_API UProtectionStrategy : public UBaseTickableObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Equip(AActor* player);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Remove();

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnPutOn OnPutOn;
	
protected:
	UPROPERTY(BlueprintReadOnly)
	AActor* Player;
};
