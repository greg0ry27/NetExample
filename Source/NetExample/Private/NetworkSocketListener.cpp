// Fill out your copyright notice in the Description page of Project Settings.

#include "NetExample.h"
#include "Async.h"
#include "pockets.pb.h"
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <google/protobuf/io/coded_stream.h>
#include "NetworkDispather.h"
#include "NetworkSocketListner.h"

using namespace com::nl::network::generated;

NetworkSocketListner* NetworkSocketListner::RunnableThread = nullptr;
FThreadSafeBool NetworkSocketListner::bIsThreadRun = false;

void NetworkSocketListner::Shutdown()
{
	bIsThreadRun = false;

	GLog->Log("FTCPSocketListeningTh::Shutdown()");

	if (RunnableThread != nullptr)
	{
		delete RunnableThread;
		RunnableThread = nullptr;
	}
}

void NetworkSocketListner::Start(TSharedPtr<FSocket> TcpSocketToSet, TSharedPtr<UNetworkDispather> DispatcherToSet)
{
	if (RunnableThread == nullptr && FPlatformProcess::SupportsMultithreading()){		
		RunnableThread = new NetworkSocketListner(TcpSocketToSet, DispatcherToSet);
	}		
}

NetworkSocketListner::NetworkSocketListner(TSharedPtr<FSocket> TcpSocketToSet, TSharedPtr<UNetworkDispather> DispatcherToSet)
{
	TcpSocket = TcpSocketToSet;
	Dispatcher = DispatcherToSet;
	Thread = FRunnableThread::Create(this, TEXT("TCP_RECEIVER"), 0, TPri_BelowNormal);
}

NetworkSocketListner::~NetworkSocketListner()
{
	delete Thread;
	Thread = nullptr;
}

bool NetworkSocketListner::Init() 
{
	bIsThreadRun = true;
	return true;
}

void NetworkSocketListner::Stop() 
{
	bIsThreadRun = false;
}
uint32 NetworkSocketListner::Run() 
{
	UE_LOG(LogTemp, Warning, TEXT("Starting read ..."));
	while (bIsThreadRun)
	{
		if (!TcpSocket.IsValid())
			return 0;

		TArray<uint8> ReceivedData;		
		

		uint32 Size;
		while (TcpSocket->HasPendingData(Size))
		{
			ReceivedData.Init(FMath::Min(Size, 65507u), Size);
			int32 Read = 0;
			TcpSocket->Recv(ReceivedData.GetData(), ReceivedData.Num(), Read);
			
		}

		

		if (ReceivedData.Num() > 0)
		{						
			UE_LOG(LogTemp, Warning, TEXT("Read data %d"), ReceivedData.Num());

			uint8_t * buffer = ReceivedData.GetData();
			size_t size = ReceivedData.Num();
									
			google::protobuf::io::ArrayInputStream DataArray(buffer, size);
			google::protobuf::io::CodedInputStream DataInput(&DataArray);
						
			while (true)
			{								
				uint32_t MessageSize;
				if (!DataInput.ReadLittleEndian32(&MessageSize)) break;
				UE_LOG(LogTemp, Warning, TEXT("Read ..."));
				// Tell the stream not to read beyond that size.
				
				google::protobuf::io::CodedInputStream::Limit limit = DataInput.PushLimit(MessageSize);

				// Parse the message.
				NetworkPocket Message;
				if(!Message.ParseFromCodedStream(&DataInput)) break;				
				Dispatcher->Dispatch(&Message);
				
					// Release the limit.
				DataInput.PopLimit(limit);
				
			}
		}
	}
	return 0;
}