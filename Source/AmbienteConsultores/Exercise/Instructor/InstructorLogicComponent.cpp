
#include "InstructorLogicComponent.h"

UInstructorLogicComponent::UInstructorLogicComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UInstructorLogicComponent::IBindToOnInstructorFeedbackDone_Implementation(const FOnInstructorFeedbackDone& Event)
{
	OnInstructorFeedbackDoneInternal.Add(Event);
}