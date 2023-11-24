
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GestureInterface.generated.h"


UINTERFACE()
class UGestureInterface : public UInterface
{
	GENERATED_BODY()
};

class AMBIENTECONSULTORES_API IGestureInterface
{
	GENERATED_BODY()

public:
   UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
   void IOnGestureDetected(EGesture Gesture);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void IOnGestureChanged(EGesture Gesture);
};
