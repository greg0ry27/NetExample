// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Network.h"
#include "NetworkDispather.h"
#include "UObject/NoExportTypes.h"
#include "GameSinglton.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class NETEXAMPLE_API UGameSinglton : public UObject
{
	GENERATED_BODY()
	
	UGameSinglton(const FObjectInitializer& ObjectInitializer);
	
public:
	
	UPROPERTY(BlueprintReadOnly)
	UNetwork * Network;

	UPROPERTY(BlueprintReadOnly)
	UNetworkDispather * Dispatcher;
};
