#pragma once
#include "EngineNet.h"

// Ό³Έν :
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

protected:
	void ServerOpen();

private:

};

