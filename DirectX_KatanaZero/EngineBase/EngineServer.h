#pragma once
#include "EngineNet.h"

// Ό³Έν :
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
};

