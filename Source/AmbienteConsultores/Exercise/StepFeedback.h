#pragma once

#include "CoreMinimal.h"
#include "AmbienteConsultores/Modules/DataAssets/ExerciseDataAsset.h"
#include "UObject/Object.h"
#include "StepFeedback.generated.h"

UCLASS(Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew)
class AMBIENTECONSULTORES_API UStepFeedback : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn="true"))
	FInstructorDialog InstructorDialog;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DoFeedback(AActor* Instructor, AActor* Player);
};
