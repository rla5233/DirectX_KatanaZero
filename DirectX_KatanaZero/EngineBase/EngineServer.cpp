#include "PreCompile.h"
#include "EngineServer.h"
#include <functional>
#include "EngineProtocol.h"
#include "NetObject.h"

UEngineServer::UEngineServer() 
{
}

UEngineServer::~UEngineServer() 
{
}

void UEngineServer::AcceptThreadFunction(UEngineServer* Server, SOCKET _AcceptSocket)
{
	int AddressLen = sizeof(SOCKADDR_IN);

	while (true == Server->IsActive())
	{
		SOCKADDR_IN ClientAdd;
		memset(&ClientAdd, 0, sizeof(ClientAdd));
		SOCKET ClientSocket = accept(_AcceptSocket, (sockaddr*)&ClientAdd, &AddressLen);

		// 에러입니다.
		if (SOCKET_ERROR == ClientSocket || INVALID_SOCKET == ClientSocket)
		{
			return;
		}

		std::shared_ptr<UTCPSession> NewSession = std::make_shared<UTCPSession>(ClientSocket);

		int Token = USession::GetNewSessionToken();
		USessionTokenPacket NewPacket;
		NewPacket.SetSessionToken(Token);


		UEngineSerializer Ser = NewPacket.GetSerialize();
		NewSession->Send(Ser);

		Server->Sessions.push_back(NewSession);

	}
}

void UEngineServer::ServerOpen(int _Port, int _BackLog /*= 512*/)
{
	Port = _Port;

	AcceptSession.Create();
	AcceptSession.Bind(_Port);

	int BackLog = 1;
	if (SOCKET_ERROR == listen(AcceptSession.GetSocket(), BackLog))
	{
		assert(false);
	}

	// 접속자가 있으면 접속자를 빼내야 하는데 쓰레로 해야한다.
	AcceptThread.SetName("AcceptThread");
	AcceptThread.Start(std::bind(AcceptThreadFunction, this, AcceptSession.GetSocket()));
}

void UEngineServer::Send(std::shared_ptr<UEngineProtocol> _Protocol)
{
	// 서버같은 경우에는 브로드캐스트를 해야한다.

	UEngineSerializer Ser = _Protocol->GetSerialize();

	for (std::shared_ptr<USession> User : Sessions)
	{
		if (false == User->IsTokenInit())
		{
			continue;
		}

		User->Send(Ser);
	}

	// 다른 모든 접속자에게 이 프로토콜을 다 보낸다.
}
