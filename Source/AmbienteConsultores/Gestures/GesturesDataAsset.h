// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "GesturesDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FHandInclinationRange
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MinInclination;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxInclination;
};

USTRUCT(BlueprintType)
struct FFingersPositions
{
	GENERATED_BODY()
	FFingersPositions()
		: SocketName(TEXT("")), BoneName(TEXT(""))
	{}
	
	FFingersPositions(FName SocketName, FName BoneName)
		: SocketName(SocketName), BoneName(BoneName)
	{}
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName SocketName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName BoneName;
};

USTRUCT(BlueprintType)
struct FGestureData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag Gesture;	

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FFingersPositions> FingersPositions
	{
		FFingersPositions("ThumbFingerOPEN", "_thumb_finger_tip_marker"),
		FFingersPositions("IndexFingerOPEN", "_index_finger_tip_marker"),
		FFingersPositions("MiddleFingerOPEN", "_middle_finger_tip_marker"),
		FFingersPositions("RingFingerOPEN", "_ring_finger_tip_marker"),
		FFingersPositions("PinkyFingerOPEN", "_pinky_finger_tip_marker")		
	};	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EControllerHand Hand;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FHandInclinationRange UpInclinationRange;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FHandInclinationRange RightInclinationRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FHandInclinationRange ForwardInclinationRange;
};

UCLASS(BlueprintType)
class AMBIENTECONSULTORES_API UGestureDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FGestureData> Gestures; 
};
