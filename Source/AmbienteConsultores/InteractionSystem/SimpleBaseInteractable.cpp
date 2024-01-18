#include "SimpleBaseInteractable.h"

#include "Components/BoxComponent.h"

ASimpleBaseInteractable::ASimpleBaseInteractable()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	MeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->AttachToComponent(MeshComponent, FAttachmentTransformRules::KeepRelativeTransform);
	BoxComponent->ComponentTags.Add("interactable-collider");
}



