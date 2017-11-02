// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NetExample.h"
#include "UObject/NoExportTypes.h"
#include "Runtime/Sockets/Public/Sockets.h"
#include "Runtime/Networking/Public/Networking.h"
#include "NetworkDispather.h"
#include "Network.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class NETEXAMPLE_API UNetwork : public UObject
{
	GENERATED_BODY()

	UNetwork(const FObjectInitializer& ObjectInitializer);
public:		

	UFUNCTION(BlueprintCallable, Category = "Network|Setup")
	bool Connect(FString host, int32 port);

	UFUNCTION(BlueprintCallable, Category = "Network|Setup")
	void Disconnect();

	UFUNCTION(BlueprintCallable, Category = "Network|Setup")
	void Login(FString user, FString pass);

	bool bIsConnection = false;

	TSharedPtr<FSocket>				TcpSocket;
	TSharedPtr<FInternetAddr>		TcpAddress;
	TSharedPtr<UNetworkDispather>	Dispatcher;
	
private:

	int BufferSize = 1024 * 1024;	
	
};
