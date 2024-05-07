#pragma once
#include "EngineNet.h"
#include "EngineThread.h"
#include "TCPSession.h"

// 설명 :
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

protected:
	void ServerOpen(int _Port, int _BackLog = 512) override;

private:
	int Port;
	UEngineThread AcceptThread;
	UTCPSession AcceptSession;

	// std::shared_ptr 쓰레드에 안전합니다.
	std::list<std::shared_ptr<USession>> Sessions;

	static void AcceptThreadFunction(UEngineServer* _Server, SOCKET _AcceptSocket);
};

