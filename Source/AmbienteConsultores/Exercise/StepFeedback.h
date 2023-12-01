#pragma once

#include "CoreMinimal.h"
#include "AmbienteConsultores/Modules/DataAssets/ExerciseDataAsset.h"
#include "UObject/Object.h"
#include "StepFeedback.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStepFeedbackDone);


UCLASS(Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew)
class AMBIENTECONSULTORES_API UStepFeedback : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn="true"))
	FInstructorFeedback InstructorFeedback;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DoFeedback(AActor* Instructor, AActor* Player);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void OnFeedbackDone();

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnStepFeedbackDone OnStepFeedbackDone;
};
