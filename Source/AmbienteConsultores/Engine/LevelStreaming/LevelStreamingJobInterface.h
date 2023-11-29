#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LevelStreamingJobInterface.generated.h"

class ILevelStreamingJobInterface;
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnLevelStreamingJobEnds, TScriptInterface<ILevelStreamingJobInterface>, Reference);

// This class does not need to be modified.
UINTERFACE()
class ULevelStreamingJobInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ILevelStreamingJobInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, DisplayName="BindOrCallToJobEnd")
	void IBindOrCallToJobEnd(const FOnLevelStreamingJobEnds& Delegate);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, DisplayName="UnbindFromJobEnd")
	void IUnbindFromJobEnd(const FOnLevelStreamingJobEnds& Delegate);
};