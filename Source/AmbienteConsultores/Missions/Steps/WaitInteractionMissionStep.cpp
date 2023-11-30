// Fill out your copyright notice in the Description page of Project Settings.


#include "WaitInteractionMissionStep.h"

#include "AmbienteConsultores/Engine/WorldRegistry/WorldRegistrySubsystem.h"
#include "AmbienteConsultores/InteractionSystem/InteractableComponent.h"
#include "AmbienteConsultores/InteractionSystem/InteractableInterface.h"

void UWaitInteractionMissionStep::Execute(AActor* InPlayerActor)
{
	Super::Execute(InPlayerActor);

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
	if(!ensureMsgf(IsValid(TargetPtr), TEXT("Target actor not found")))
	{
		EndExecution(false);
		return;
	}
	Interactable = TargetPtr->FindComponentByClass<UInteractableComponent>();
	FOnInteractionStart Delegate;
	Delegate.BindDynamic(this, &ThisClass::OnInteracted);
	IInteractableInterface::Execute_IBindToOnInteractionStarted(Interactable.GetObject(), Delegate);
}

void UWaitInteractionMissionStep::Cancel()
{
	if(IsValid(Interactable.GetObject()))
	{
		FOnInteractionStart Delegate;
		Delegate.BindDynamic(this, &ThisClass::OnInteracted);
		IInteractableInterface::Execute_IBindToOnInteractionStarted(Interactable.GetObject(), Delegate);
	}
	Interactable = nullptr;
	Super::Cancel();
}

void UWaitInteractionMissionStep::OnInteracted(AActor* Instigator, AActor* Fill)
{
	if(IsValid(Interactable.GetObject()) && Instigator == PlayerActor)
	{
		IInteractableInterface::Execute_ISetEnabled(Interactable.GetObject(), !bDisableAfterInteraction);
		EndExecution(true);
		Interactable = nullptr;
	}
}
