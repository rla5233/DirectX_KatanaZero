#pragma once
#include "EngineNet.h"
#include "EngineThread.h"
#include "TCPSession.h"

// ���� :
class UEngineServer : public UEngineNet
{
public:
	// constrcuter destructer
	UEngineServer();
	~UEngineServer();

	// delete Function
	UEngineServer(const UEngineServer& _Other) = delete;
	UEngineServer(UEngineServer&& _Other) noexcept = delete;
	UEngineServer& operator=(const UEngineServer& _Other) = delete;
	UEngineServer& operator=(UEngineServer&& _Other) noexcept = delete;

	void Send(std::shared_ptr<UEngineProtocol> _Protocol) override;

protected:
	void ServerOpen(int _Port, int _BackLog = 512) override;

private:
	int Port;
	UEngineThread AcceptThread;
	UTCPSession AcceptSession;

	// std::shared_ptr �����忡 �����մϴ�.
	std::list<std::shared_ptr<USession>> Sessions;

	static void AcceptThreadFunction(UEngineServer* _Server, SOCKET _AcceptSocket);
};

