#pragma once

#include "CoreMinimal.h"
#include "AmbienteConsultores/Modules/DataAssets/ExerciseDataAsset.h"
#include "AmbienteConsultores/Utils/BaseTickableObject.h"
#include "BaseStepFeedback.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStepFeedbackDone, UBaseStepFeedback*, Feedback);



UCLASS(Blueprintable, BlueprintType, EditInlineNew)
class AMBIENTECONSULTORES_API UBaseStepFeedback : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DoFeedback(AActor* instructor, AActor* player);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void OnFeedbackDone();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UBaseStepFeedback* CloneFromDef(UObject* Outer);

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnStepFeedbackDone OnStepFeedbackDone;

	UPROPERTY(BlueprintReadOnly)
	AActor* Instructor;

	UPROPERTY(BlueprintReadOnly)
	AActor* Player;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FInstructorFeedback InstructorFeedback;	
};
