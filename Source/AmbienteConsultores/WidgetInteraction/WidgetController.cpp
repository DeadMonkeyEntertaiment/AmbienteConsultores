// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetController.h"

#include "WidgetComponentGameplayTag.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

void UWidgetController::InitializeWidgetController(UWidgetComponentGameplayTag* WidgetComponentRef)
{
	WidgetComponent = WidgetComponentRef;
	Widget = CreateWidget(UGameplayStatics::GetPlayerController(GetWorld(), 0),WidgetClass);
	WidgetComponent->SetWidget(Widget);
	ToggleWidgetComponentVisibility_Implementation(false);
}

void UWidgetController::ToggleWidgetComponentVisibility_Implementation(bool NewVisibility)
{
	WidgetComponent->SetHiddenInGame(!NewVisibility, true);	
	WidgetComponent->SetCollisionEnabled(NewVisibility ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision);	
}
