
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGrabbable.generated.h"

UCLASS(Blueprintable)
class AMBIENTECONSULTORES_API ABaseGrabbable : public AActor
{
	GENERATED_BODY()

public:	
	ABaseGrabbable();

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* MeshComponent;
};
