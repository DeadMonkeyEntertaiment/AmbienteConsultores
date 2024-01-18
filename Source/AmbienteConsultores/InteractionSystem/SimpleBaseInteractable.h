#pragma once

#include "CoreMinimal.h"
#include "BaseInteractable.h"
#include "GameFramework/Actor.h"
#include "SimpleBaseInteractable.generated.h"

class UBoxComponent;
UCLASS()
class AMBIENTECONSULTORES_API ASimpleBaseInteractable : public ABaseInteractable
{
	GENERATED_BODY()

public:

	ASimpleBaseInteractable();
	
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxComponent;


};
