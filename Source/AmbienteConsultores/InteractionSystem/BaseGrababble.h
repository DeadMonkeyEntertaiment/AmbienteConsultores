
#pragma once

#include "CoreMinimal.h"
#include "BaseInteractable.h"
#include "BaseGrababble.generated.h"

UCLASS()
class AMBIENTECONSULTORES_API ABaseGrababble : public ABaseInteractable
{
	GENERATED_BODY()

public:
	ABaseGrababble();

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* MeshComponent;

};
