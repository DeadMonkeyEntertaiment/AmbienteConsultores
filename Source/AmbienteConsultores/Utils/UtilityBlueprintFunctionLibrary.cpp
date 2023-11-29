
#include "UtilityBlueprintFunctionLibrary.h"

UActorComponent* UUtilityBlueprintFunctionLibrary::GetValidatedComponentByClass(AActor* Target,
                                                                                TSubclassOf<UActorComponent> ComponentClass, TEnumAsByte<EValidationPins>& Outcome)
{
	if (!IsValid(Target))
	{
		Outcome = EValidationPins::NotValid;
		return nullptr;
	}
	UActorComponent* Component = Target->FindComponentByClass(ComponentClass);
	Outcome = IsValid(Component)
		          ? EValidationPins::Valid
		          : EValidationPins::NotValid;
	return Component;
}

TArray<UActorComponent*> UUtilityBlueprintFunctionLibrary::GetValidatedComponentsByClass(AActor* Target,
                                                                                         const TSubclassOf<UActorComponent> ComponentClass, TEnumAsByte<EValidationPins>& Outcome)
{
	if (!IsValid(Target))
	{
		Outcome = EValidationPins::NotValid;
		return TArray<UActorComponent*>();
	}

	TArray<UActorComponent*> FoundComponents;
	
	if (UClass* TargetClass = ComponentClass.Get())
	{
		for (UActorComponent* Component : Target->GetComponents())
		{
			if (Component && Component->IsA(TargetClass) && IsValid(Component))
				FoundComponents.Add(Component);
		}
	}

	Outcome = FoundComponents.Num() > 0 ? EValidationPins::Valid : EValidationPins::NotValid;
	return FoundComponents;
}