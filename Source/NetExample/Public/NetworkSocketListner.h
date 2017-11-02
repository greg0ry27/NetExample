// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NetExample.h"
#include "NetworkDispather.h"
#include "Runtime/Sockets/Public/Sockets.h"
#include "Runtime/Core/Public/HAL/Runnable.h"
#include "Runtime/Core/Public/HAL/ThreadSafeBool.h"

/**
 * 
 */
class NetworkSocketListner:public FRunnable
{
	/** Thread to run the worker FRunnable on */
	FRunnableThread* Thread;

	/** Singleton instance, can access the thread any time via static accessor, if it is active! */	
	static NetworkSocketListner * RunnableThread;
	static FThreadSafeBool bIsThreadRun;

public:
	

	NetworkSocketListner(TSharedPtr<FSocket> TcpSocketToSet, TSharedPtr<UNetworkDispather> DispatcherToSet);

	~NetworkSocketListner();

	// Begin FRunnable interface.
	virtual bool	Init();
	virtual uint32	Run();
	virtual void	Stop();
	// End FRunnable interface.

	static void Shutdown();
	static void Start(TSharedPtr<FSocket> TcpSocketToSet, TSharedPtr<UNetworkDispather> DispatcherToSet);

private:
	TSharedPtr<FSocket> TcpSocket;
	TSharedPtr<UNetworkDispather> Dispatcher;
};
