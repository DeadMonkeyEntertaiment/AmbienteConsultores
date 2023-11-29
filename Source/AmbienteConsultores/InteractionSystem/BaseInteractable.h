#pragma once

#include "CoreMinimal.h"
#include "InteractableComponent.h"
#include "GameFramework/Actor.h"
#include "BaseInteractable.generated.h"

UCLASS()
class AMBIENTECONSULTORES_API ABaseInteractable : public AActor
{
	GENERATED_BODY()

public:
	ABaseInteractable();	

	UPROPERTY(EditDefaultsOnly)
	UInteractableComponent* InteractableComponent;
};
