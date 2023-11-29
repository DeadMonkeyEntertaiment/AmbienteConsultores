// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTriggerMissionStep.h"

#include "AmbienteConsultores/Entities/TriggerActorInterface.h"


void UPlayerTriggerMissionStep::Execute(AActor* InPlayerActor)
{
	Super::Execute(InPlayerActor);

	if(!ensureMsgf(!Trigger.IsNull() && Trigger->GetClass()->ImplementsInterface(UTriggerActorInterface::StaticClass()), TEXT("Invalid trigger.")))
	{
		EndExecution(false);
		return;
	}
	FTriggerInteractionEvent Event;
	Event.BindDynamic(this, &UPlayerTriggerMissionStep::OnTriggerExecuted);
	ITriggerActorInterface::Execute_IBindToTriggerInteraction(Trigger.Get(), Event);
}

void UPlayerTriggerMissionStep::Cancel()
{
	FTriggerInteractionEvent Event;
	Event.BindDynamic(this, &UPlayerTriggerMissionStep::OnTriggerExecuted);
	ITriggerActorInterface::Execute_IUnbindFromTriggerInteraction(Trigger.Get(), Event);
	Super::Cancel();
}

#if WITH_EDITOR
FText UPlayerTriggerMissionStep::GetNodeTitle() const
{
	if(!Trigger.IsValid())
		return Super::GetNodeTitle();
	
	return FText().FromString(Super::GetNodeTitle().ToString() + "["+ Trigger.Get()->GetName() +"]");
}
#endif

void UPlayerTriggerMissionStep::OnTriggerExecuted(FTriggerInteractionInfo InteractionInfo)
{
	if (PlayerActor == InteractionInfo.Instigator)
	{
		// Ends on enter and interaction is active or ends on exit and interaction is over.
		if ((!bFinishOnExit && InteractionInfo.bIsInteractionActive) ||
			(bFinishOnExit && !InteractionInfo.bIsInteractionActive))
		{
			FTriggerInteractionEvent Event;
			Event.BindDynamic(this, &UPlayerTriggerMissionStep::OnTriggerExecuted);
			ITriggerActorInterface::Execute_IUnbindFromTriggerInteraction(Trigger.Get(), Event);
			EndExecution(true);
		}
	}
}
