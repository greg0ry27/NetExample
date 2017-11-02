// Fill out your copyright notice in the Description page of Project Settings.

#include "NetExample.h"
#include "NetworkDispather.h"

using namespace com::nl::network::generated;

void  UNetworkDispather::Dispatch(NetworkPocket * pocket) 
{
	FString t = FString(pocket->GetTypeName().c_str());
	UE_LOG(LogTemp, Warning, TEXT("Dispatch pocket: %s"), *t);
}

