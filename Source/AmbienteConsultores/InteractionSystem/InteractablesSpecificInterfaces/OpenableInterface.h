
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "OpenableInterface.generated.h"


DECLARE_DYNAMIC_DELEGATE(FOnOpenableInteraction);


UINTERFACE()
class UOpenableInterface : public UInterface
{
	GENERATED_BODY()
};


class AMBIENTECONSULTORES_API IOpenableInterface
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Binding")
	void IBindToOnOpened(const FOnOpenableInteraction& Event);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Binding")
	void IBindToOnClosed(const FOnOpenableInteraction& Event);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "State")
	bool IsOpen();

};
