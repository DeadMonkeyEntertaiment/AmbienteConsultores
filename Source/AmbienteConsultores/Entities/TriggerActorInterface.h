#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TriggerActorInterface.generated.h"

USTRUCT(BlueprintType)
struct FTriggerInteractionInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite) AActor* Instigator = nullptr;
	UPROPERTY(BlueprintReadWrite) bool bIsInteractionActive = false;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FTriggerInteractionEvent, FTriggerInteractionInfo, InteractionInfo);

// This class does not need to be modified.
UINTERFACE()
class UTriggerActorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ITriggerActorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	public:

	UFUNCTION(BlueprintNativeEvent, DisplayName="BindToActorInteract") void IBindToTriggerInteraction(const FTriggerInteractionEvent& Event);
	UFUNCTION(BlueprintNativeEvent, DisplayName="UnbindFromActorInteract") void IUnbindFromTriggerInteraction(const FTriggerInteractionEvent& Event);
};