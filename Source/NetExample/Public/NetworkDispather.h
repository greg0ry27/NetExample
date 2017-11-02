// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "pockets.pb.h"
#include "NetworkDispather.generated.h"

using namespace com::nl::network::generated;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFailDelegate, FString, ErrorCode, FString, ErrorDesc);
/**
 * 
 */
UCLASS(Blueprintable)
class NETEXAMPLE_API UNetworkDispather : public UObject
{
	GENERATED_BODY()
	
public:

	void Dispatch(NetworkPocket * pocket);

	UPROPERTY(BlueprintAssignable, Category = "Network|Dispatcher|Setup")
	FOnFailDelegate OnFail;
	
};
