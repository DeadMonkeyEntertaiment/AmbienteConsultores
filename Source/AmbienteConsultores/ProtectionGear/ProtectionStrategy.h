
#pragma once

#include "CoreMinimal.h"
#include "AmbienteConsultores/Utils/BaseTickableObject.h"
#include "ProtectionStrategy.generated.h"

UCLASS(Blueprintable, BlueprintType, EditInlineNew)
class AMBIENTECONSULTORES_API UProtectionStrategy : public UBaseTickableObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PutOn(AActor* player);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Remove();

protected:
	UPROPERTY(BlueprintReadOnly)
	AActor* Player;
};
