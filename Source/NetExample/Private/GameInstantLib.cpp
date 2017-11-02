// Fill out your copyright notice in the Description page of Project Settings.

#include "NetExample.h"
#include "GameInstantLib.h"


UGameInstantLib::UGameInstantLib(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}

UNetwork * UGameInstantLib::GetNetwork()
{
	UGameSinglton* DataInstance = Cast<UGameSinglton>(GEngine->GameSingleton);

	if (DataInstance != nullptr)
		return DataInstance->Network;

	return nullptr;
}

UNetworkDispather * UGameInstantLib::GetNetworkDispatcher()
{
	UGameSinglton* DataInstance = Cast<UGameSinglton>(GEngine->GameSingleton);

	if (DataInstance != nullptr)
		return DataInstance->Dispatcher;

	return nullptr;
}
