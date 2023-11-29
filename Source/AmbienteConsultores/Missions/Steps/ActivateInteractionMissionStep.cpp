// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivateInteractionMissionStep.h"

#include "AmbienteConsultores/Engine/WorldRegistry/WorldRegistrySubsystem.h"
#include "AmbienteConsultores/InteractionSystem/InteractableComponent.h"

void UActivateInteractionMissionStep::Execute(AActor* InPlayerActor)
{
	Super::Execute(InPlayerActor);

	AActor* TargetPtr = nullptr;
	if(bFindUsingRegistry)
	{
		if(!ensureMsgf(IsValid(ActorClass), TEXT("ActorClass is not set.")))
		{
			EndExecution(false);
			return;
		}
		
		
		UWorldRegistrySubsystem* WorldRegistrySubsystem = InPlayerActor->GetWorld()->GetSubsystem<UWorldRegistrySubsystem>();
		TargetPtr = WorldRegistrySubsystem->GetWorldRegistry()->FindActorWithTag(ActorClass, ActorTag);
	}
	else
	{
		ensureMsgf(!TargetActor.IsNull(), TEXT("TargetActor not set."));
		TargetPtr = TargetActor.Get();
	}

	UInteractableComponent* InteractableComponent = TargetPtr->FindComponentByClass<UInteractableComponent>();
	if(!ensureMsgf(IsValid(InteractableComponent), TEXT("Interactable component not found in target.")))
	{
		EndExecution(false);
		return;
	}
	IInteractableInterface::Execute_IStartInteraction(InteractableComponent, InPlayerActor);
	IInteractableInterface::Execute_ISetEnabled(InteractableComponent, !bDisableAfterInteraction);
	EndExecution(true);
}
