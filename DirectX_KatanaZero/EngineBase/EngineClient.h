#pragma once
#include "EngineNet.h"
#include "TCPSession.h"

// ���� :
class UEngineClient : public UEngineNet
{
public:
	// constrcuter destructer
	UEngineClient();
	~UEngineClient();

	// delete Function
	UEngineClient(const UEngineClient& _Other) = delete;
	UEngineClient(UEngineClient&& _Other) noexcept = delete;
	UEngineClient& operator=(const UEngineClient& _Other) = delete;
	UEngineClient& operator=(UEngineClient&& _Other) noexcept = delete;

	void Send(std::shared_ptr<UEngineProtocol> _Protocol) override;

protected:
	void ServerOpen(int _Port, int _BackLog) override;
	void Connect(std::string _Ip, int _Port) override;

private:
	UTCPSession Session;
};

