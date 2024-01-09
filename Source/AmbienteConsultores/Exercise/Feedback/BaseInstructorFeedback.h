#pragma once

#include "CoreMinimal.h"
#include "BaseStepFeedback.h"
#include "AmbienteConsultores/Modules/DataAssets/ExerciseDataAsset.h"
#include "BaseInstructorFeedback.generated.h"


UCLASS(Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew)
class AMBIENTECONSULTORES_API UBaseInstructorFeedback : public UBaseStepFeedback
{
	GENERATED_BODY()

public:
	virtual void DoFeedback_Implementation(AActor* instructor, AActor* player) override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn="true"))
	FInstructorFeedback InstructorFeedback;

	UPROPERTY(BlueprintReadOnly)
	AActor* Instructor;

	UPROPERTY(BlueprintReadOnly)
	AActor* Player;
	
};
