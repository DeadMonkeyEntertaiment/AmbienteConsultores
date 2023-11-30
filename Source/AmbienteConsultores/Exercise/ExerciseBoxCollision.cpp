#include "ExerciseBoxCollision.h"

#include "Components/BoxComponent.h"


AExerciseBoxCollision::AExerciseBoxCollision()
{

	PrimaryActorTick.bCanEverTick = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxComponent->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);
}


