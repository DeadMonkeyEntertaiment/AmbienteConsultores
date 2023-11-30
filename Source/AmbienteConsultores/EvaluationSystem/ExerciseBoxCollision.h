#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "ExerciseBoxCollision.generated.h"


class UBoxComponent;
UCLASS()
class AMBIENTECONSULTORES_API AExerciseBoxCollision : public AActor
{
	GENERATED_BODY()

public:
	AExerciseBoxCollision();
	
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag BoxTag;
};
