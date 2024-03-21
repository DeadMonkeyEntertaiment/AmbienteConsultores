// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_ScoreSubsystem.h"

#include "HttpModule.h"
#include "AmbienteConsultores/EvaluationSystem/EvaluationSubsystem.h"

void UAC_ScoreSubsystem::SendScore(const TArray<FExerciseEvaluation>& Evaluations)
{
	FString ContentString;
	const TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	if(Evaluations.Num() > 0)
	{
		JsonObject->SetStringField(TEXT("courseId"), Evaluations[0].Exercise.ToString());
	}

	FString StepsString;
	const TSharedRef<TJsonWriter<>> StepsWriter = TJsonWriterFactory<>::Create(&StepsString);
	StepsWriter->WriteArrayStart();
	for (const FExerciseEvaluation& Evaluation : Evaluations)
	{
		TSharedPtr<FJsonObject> EvalObject = Evaluation.ToJsonObject();
		FJsonSerializer::Serialize(EvalObject.ToSharedRef(), StepsWriter);
	}
	StepsWriter->WriteArrayEnd();
	StepsWriter->Close();

	JsonObject->SetStringField(TEXT("steps"), StepsString);

	const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&ContentString);
	if (FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer))
	{
		const FString URL = TEXT("https://api.indielevelstudio.com/api/trainings/score");
		const TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
		HttpRequest->SetURL(URL);
		HttpRequest->SetVerb(TEXT("POST"));
		HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
		HttpRequest->SetContentAsString(ContentString);
		HttpRequest->OnProcessRequestComplete().BindUObject(this, &UAC_ScoreSubsystem::OnResponseReceived);
		HttpRequest->ProcessRequest();
	}
}

void UAC_ScoreSubsystem::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
}
