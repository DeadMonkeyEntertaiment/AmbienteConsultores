
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EnhancedInput.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnInputAction);

UCLASS(BlueprintType)
class AMBIENTECONSULTORES_API UEnhancedInput : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	static void SetupInputComponent(UObject* Context, UInputAction* ClickAction, FOnInputAction OnInputActionStart, FOnInputAction OnInputActionEnd);

};
