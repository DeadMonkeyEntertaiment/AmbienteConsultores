
#pragma once

#include "CoreMinimal.h"
#include "LevelStreamingJobInterface.h"
#include "UObject/Object.h"
#include "LevelStreamingJob.generated.h"



/**
 * 
 */
UCLASS(BlueprintType)
class ULevelStreamingJob : public UObject, public ILevelStreamingJobInterface
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void Begin();

	UFUNCTION() void Setup(TArray<TSoftObjectPtr<UWorld>> LevelsToProcess, bool IsLoadJob,
		bool VisibleAfterLoad, bool BlockOnLoad);

	virtual void IBindOrCallToJobEnd_Implementation(const FOnLevelStreamingJobEnds& Delegate) override;
	virtual void IUnbindFromJobEnd_Implementation(const FOnLevelStreamingJobEnds& Delegate) override;


private:
	//Load process
	UFUNCTION() void LoadNext();
	UFUNCTION() void OnActionEnded();
	UFUNCTION() void BroadcastJobEnd();

	//Interface required properties.
	UPROPERTY() TArray<FOnLevelStreamingJobEnds> JobEndedDelegates;
	UPROPERTY() bool bFinished;

	UPROPERTY() bool bIsLoadJob = true;
	UPROPERTY() bool bMakeVisibleAfterLoad = true;
	UPROPERTY() bool bBlockOnLevelLoad = true;
	UPROPERTY() TArray<TSoftObjectPtr<UWorld>> LevelsLeft;
};