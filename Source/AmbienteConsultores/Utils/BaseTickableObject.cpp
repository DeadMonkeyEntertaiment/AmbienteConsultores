// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTickableObject.h"

void UBaseTickableObject::CustomTimer(AActor* Actor, float Time, bool Looping, float StartDelay)
{ 
	Actor->GetWorld()->GetTimerManager().SetTimer(MemberTimerHandle, this, &UBaseTickableObject::TimerFunction, Time, Looping, StartDelay);	
}

void UBaseTickableObject::Tick(float DeltaTime)
{	
	ObjectTick(DeltaTime);
}
