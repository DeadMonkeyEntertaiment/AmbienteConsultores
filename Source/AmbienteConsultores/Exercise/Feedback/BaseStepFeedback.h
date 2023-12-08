#pragma once

#include "CoreMinimal.h"
#include "AmbienteConsultores/Modules/DataAssets/ExerciseDataAsset.h"
#include "AmbienteConsultores/Utils/BaseTickableObject.h"
#include "BaseStepFeedback.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStepFeedbackDone);

UCLASS(Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew)
class AMBIENTECONSULTORES_API UBaseStepFeedback : public UBaseTickableObject
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
