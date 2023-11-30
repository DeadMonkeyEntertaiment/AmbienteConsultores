#include "ExerciseEvaluationStrategy.h"

#include "ExerciseBoxCollision.h"
#include "AmbienteConsultores/InteractionSystem/BaseInteractable.h"
#include "Components/BoxComponent.h"
/*
void UExerciseEvaluationStrategy::SetupEvaluationBindings_Implementation()
{

	for (TSoftObjectPtr<ABaseInteractable> InteractActor: InteractActors)
	{
		UInteractableComponent* InteractableComponent = InteractActor.Get()->FindComponentByClass<UInteractableComponent>();

		FOnInteractionStart InteractionStartedActivationReqHandler;			
		InteractionStartedActivationReqHandler.BindDynamic(this, &UExerciseEvaluationStrategy::OnInteractionStarted);
		IInteractableInterface::Execute_IBindToOnInteractionStarted(InteractableComponent, InteractionStartedActivationReqHandler);


		FOnInteractionGoalAchieved InteractionGoalActivationReqHandler;	
		InteractionGoalActivationReqHandler.BindDynamic(this, &UExerciseEvaluationStrategy::OnInteractionGoalAchieved);
		IInteractableInterface::Execute_IBindToOnInteractionGoalAchieved(InteractableComponent, InteractionGoalActivationReqHandler);		
		
		FOnInteractionFinished ForceFinishInteractionActivationReqHandler;
		ForceFinishInteractionActivationReqHandler.BindDynamic(this, &UExerciseEvaluationStrategy::OnInteractionFinished);
		IInteractableInterface::Execute_IBindToOnInteractionFinished(InteractableComponent, ForceFinishInteractionActivationReqHandler);
	}
	
	for (TSoftObjectPtr<AExerciseBoxCollision> BoxCollider : BoxColliders)
	{
		UBoxComponent* BoxComponent = BoxCollider.Get()->FindComponentByClass<UBoxComponent>();
		BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &UExerciseEvaluationStrategy::OnBoxBeginOverlap);
	}
}*/
