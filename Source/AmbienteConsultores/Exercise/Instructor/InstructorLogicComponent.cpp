
#include "InstructorLogicComponent.h"

UInstructorLogicComponent::UInstructorLogicComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInstructorLogicComponent::IBindToOnInstructorFeedbackDone_Implementation(const FOnInstructorFeedbackDone& Event)
{
	OnInstructorFeedbackDoneInternal.Add(Event);
}

void UInstructorLogicComponent::IUnbindFromOnInstructorFeedbackDone_Implementation(
	const FOnInstructorFeedbackDone& Event)
{
	OnInstructorFeedbackDoneInternal.Remove(Event);
}
