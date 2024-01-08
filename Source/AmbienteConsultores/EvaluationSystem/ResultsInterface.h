

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ResultsInterface.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnBackToMainMenuClicked);

UINTERFACE()
class UResultsInterface : public UInterface
{
	GENERATED_BODY()
};

class AMBIENTECONSULTORES_API IResultsInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void IShowResults(const TArray<FExerciseEvaluation> &ExercisesEvaluations);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void IBindToOnBackToMainMenuClicked(const FOnBackToMainMenuClicked& Event);


};
