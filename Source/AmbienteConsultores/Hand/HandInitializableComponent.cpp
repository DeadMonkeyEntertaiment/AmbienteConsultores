

#include "HandInitializableComponent.h"

#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"


UHandInitializableComponent::UHandInitializableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UHandInitializableComponent::BindInputAction(UInputAction* InputAction, FOnInputActionEvent OnInputActionStart,
											  FOnInputActionEvent OnInputActionEnd)
{
	const APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UEnhancedInputComponent* EnhancedInputComponent = PlayerController->FindComponentByClass<UEnhancedInputComponent>();
	
	EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Started, GetWorld(), OnInputActionStart.GetFunctionName());
	EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Completed, GetWorld(), OnInputActionEnd.GetFunctionName());	
}
