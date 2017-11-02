// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSinglton.h"
#include "Network.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameInstantLib.generated.h"

/**
 * 
 */
UCLASS()
class NETEXAMPLE_API UGameInstantLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UGameInstantLib(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintPure, Category = "Game Singleton")
	static UNetwork * GetNetwork();

	UFUNCTION(BlueprintPure, Category = "Game Singleton")
	static UNetworkDispather * GetNetworkDispatcher();
};
