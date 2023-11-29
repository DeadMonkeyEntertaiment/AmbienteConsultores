#include "BaseInteractable.h"

ABaseInteractable::ABaseInteractable()
{	
	PrimaryActorTick.bCanEverTick = true;

	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("InteractableComponent"));
}
