// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTickableObject.h"


void UBaseTickableObject::Tick(float DeltaTime)
{	
	ObjectTick(DeltaTime);
}

bool UBaseTickableObject::IsAllowedToTick() const
{
	return TickEnable;
}
