// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaySequenceMissionStep.h"

#include "AmbienteConsultores/Engine/Sequences/SequenceSubsystem.h"

void UPlaySequenceMissionStep::Execute(AActor* InPlayerActor)
{
	Super::Execute(InPlayerActor);

	if(!SequenceToPlay)
	{
		EndExecution(true);
		return;
	}
	FFinishedCutsceneDelegate Delegate;
	Delegate.BindDynamic(this ,&UPlaySequenceMissionStep::OnSequenceFinished);
	AuxSubsystemRef = InPlayerActor->GetWorld()->GetGameInstance()->GetSubsystem<USequenceSubsystem>();
	AuxSubsystemRef->PlayOrderedCutscene(SequenceToPlay, Delegate, SequenceSettings);
}

void UPlaySequenceMissionStep::Cancel()
{
	AuxSubsystemRef->SkipCutscene();
	Super::Cancel();
}

void UPlaySequenceMissionStep::OnSequenceFinished()
{
	EndExecution(true);
}