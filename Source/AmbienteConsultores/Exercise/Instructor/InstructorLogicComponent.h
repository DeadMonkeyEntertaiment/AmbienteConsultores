#pragma once

#include "CoreMinimal.h"
#include "InstructorInterface.h"
#include "Components/ActorComponent.h"
#include "InstructorLogicComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType)
class AMBIENTECONSULTORES_API UInstructorLogicComponent : public UActorComponent, public IInstructorInterface
{
	GENERATED_BODY()

public:
	UInstructorLogicComponent();

};
