// Fill out your copyright notice in the Description page of Project Settings.

#include "NetExample.h"
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <google/protobuf/io/coded_stream.h>
#include "pockets.pb.h"
#include "NetworkSocketListner.h"
#include "Network.h"

using namespace com::nl::network::generated;

UNetwork::UNetwork(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	auto DispatcherPtr = ObjectInitializer.CreateDefaultSubobject<UNetworkDispather>(this, FName("Network Dispatcher"));
	Dispatcher = TSharedPtr<UNetworkDispather>(DispatcherPtr);
}

bool UNetwork::Connect(FString host, int32 port)
{
	if (bIsConnection)
		return true;

	// Create tcp socket
	auto Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("TCP_SOCKET"), false);
	TcpSocket = TSharedPtr<FSocket>(Socket);
	// Create a proper FInternetAddr representation
	TcpAddress = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();

	// Parse server address 
	FIPv4Address serverIP;
	FIPv4Address::Parse(host, serverIP);

	// and set 
	TcpAddress->SetIp(serverIP.Value);
	TcpAddress->SetPort(port);

	bIsConnection = TcpSocket->Connect(*TcpAddress);

	if (bIsConnection)
		NetworkSocketListner::Start(TcpSocket, Dispatcher);

	UE_LOG(LogTemp, Warning, TEXT("Connect ..."));
	return bIsConnection;
}


void UNetwork::Disconnect()
{
	if (TcpSocket.IsValid())
	{
		NetworkSocketListner::Shutdown();
		TcpSocket->Close();
		TcpSocket.Reset();
	}
	bIsConnection = false;
	UE_LOG(LogTemp, Warning, TEXT("Disconnect ..."));
}

void UNetwork::Login(FString user, FString pass) {

	if (!bIsConnection)
		return;

	UE_LOG(LogTemp, Warning, TEXT("Login ..."));
	NetworkPocket Pocket;
	
	Pocket.set_type(PocketType::LOGIN);
	NLLogin Login;		
	std::string strUser(TCHAR_TO_UTF8(*user));
	std::string strPass(TCHAR_TO_UTF8(*pass));

	Login.set_allocated_login(&strUser);
	Login.set_allocated_password(&strPass);

	Pocket.set_allocated_login(&Login);

	size_t PocketSize = Pocket.ByteSize();
	size_t size = PocketSize + 4;
	
	uint8_t * buffer = new uint8_t[size];

	google::protobuf::io::ArrayOutputStream arr(buffer, size);
	google::protobuf::io::CodedOutputStream output(&arr);

	output.WriteLittleEndian32(Pocket.ByteSize());
	Pocket.SerializeToCodedStream(&output);
	
	int32 bytesSent = 0;	
	
	TcpSocket->Send(buffer, output.ByteCount(), bytesSent);

	Pocket.release_login();
	Login.release_login();
	Login.release_password();

	delete[] buffer;
}

