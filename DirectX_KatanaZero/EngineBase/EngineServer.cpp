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

		// �����Դϴ�.
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

		// Ŭ���̾�Ʈ 1���� ���ú꾲���带 ��������� ��밡 �����ߴٸ�
		// �׳༮�� ���� �غ� �ȰŴ�.
		// ƼŰŸ���� �������ؾ� �Ѵ�.
		std::shared_ptr<UEngineThread> ClientRecvThread = std::make_shared<UEngineThread>();
		ClientRecvThread->SetName("Server Recv Thread " + std::to_string(Token));
		ClientRecvThread->Start(std::bind(UEngineNet::RecvThreadFunction, NewSession.get(), Server));

		Server->SessionRecvs.push_back(ClientRecvThread);
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

	// �����ڰ� ������ �����ڸ� ������ �ϴµ� ������ �ؾ��Ѵ�.
	AcceptThread.SetName("AcceptThread");
	AcceptThread.Start(std::bind(AcceptThreadFunction, this, AcceptSession.GetSocket()));
}

void UEngineServer::Send(std::shared_ptr<UEngineProtocol> _Protocol)
{
	// �������� ��쿡�� ��ε�ĳ��Ʈ�� �ؾ��Ѵ�.

	UEngineSerializer Ser = _Protocol->GetSerialize();

	for (std::shared_ptr<USession> User : Sessions)
	{
		if (false == User->IsTokenInit())
		{
			continue;
		}

		User->Send(Ser);
	}

	// �ٸ� ��� �����ڿ��� �� ���������� �� ������.
}
