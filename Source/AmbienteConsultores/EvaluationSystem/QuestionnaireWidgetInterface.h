

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "QuestionnaireWidgetInterface.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnAnswerReleasd, int32, AnswerNumber);

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
	void ISetupQuestion(const FQuestion& Question);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void IDoAnswerFeedback(const bool Correct, const int32 AnswerNumber);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void IBindToOnAnswerReleased(const FOnAnswerReleasd& Event);
};
