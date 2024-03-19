#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BackToMenuWidgetInterface.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnButtonClickedReleased);



UINTERFACE()
class UBackToMenuWidgetInterface : public UInterface
{
	GENERATED_BODY()
};


class AMBIENTECONSULTORES_API IBackToMenuWidgetInterface
{
	GENERATED_BODY()	
	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void IBindToYesReleased(const FOnButtonClickedReleased& Event);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void IBindToNoReleased(const FOnButtonClickedReleased& Event);
};
