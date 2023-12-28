
#pragma once

#include "CoreMinimal.h"
#include "AmbienteConsultores/Utils/BaseTickableObject.h"
#include "ProtectionStrategy.generated.h"

UCLASS(Blueprintable, BlueprintType)
class AMBIENTECONSULTORES_API UProtectionStrategy : public UBaseTickableObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PutOn(AActor* Player);

	UPROPERTY(EditAnywhere)
	bool test;
};
