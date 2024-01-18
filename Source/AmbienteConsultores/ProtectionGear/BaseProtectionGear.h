
#pragma once

#include "CoreMinimal.h"
#include "AmbienteConsultores/InteractionSystem/BaseGrababble.h"
#include "AmbienteConsultores/InteractionSystem/SimpleBaseInteractable.h"
#include "GameFramework/Actor.h"
#include "BaseProtectionGear.generated.h"

class UProtectionGearComponent;
UCLASS()
class AMBIENTECONSULTORES_API ABaseProtectionGear : public ASimpleBaseInteractable
{
	GENERATED_BODY()

public:
	ABaseProtectionGear();
	
	UPROPERTY(EditDefaultsOnly)
	UProtectionGearComponent* ProtectionGearComponent;
};
