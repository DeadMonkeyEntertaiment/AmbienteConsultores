#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameplayTags.h"
#include "WidgetComponentGameplayTag.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AMBIENTECONSULTORES_API UWidgetComponentGameplayTag : public UWidgetComponent
{
	GENERATED_BODY()

public:	
	UWidgetComponentGameplayTag();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag WidgetTag;
};
