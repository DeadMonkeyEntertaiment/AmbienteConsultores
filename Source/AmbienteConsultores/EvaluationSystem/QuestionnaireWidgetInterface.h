

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "QuestionnaireWidgetInterface.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnAnswerReleasd, int32, AnswerNumber);
DECLARE_DYNAMIC_DELEGATE(FOnQuestionnaireFinished);

UINTERFACE()
class UQuestionnaireWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

class AMBIENTECONSULTORES_API IQuestionnaireWidgetInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void IBindToOnAnswerReleased(const FOnAnswerReleasd& Event);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ISetupWidget(const FQuestion& Question);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void IAnswerFeedback(const bool Correct, const int32 AnswerNumber);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void IShowResults(const int32 Score, const int32 TotalQuestions);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void IBindToOnQuestionnaireFinished(const FOnQuestionnaireFinished& Event);


};
