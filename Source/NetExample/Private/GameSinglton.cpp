// Fill out your copyright notice in the Description page of Project Settings.

#include "NetExample.h"
#include "GameSinglton.h"



UGameSinglton::UGameSinglton(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Network = ObjectInitializer.CreateDefaultSubobject<UNetwork>(this, FName("Network"));
	Dispatcher = Network->Dispatcher.Get();
}
