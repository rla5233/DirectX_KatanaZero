#pragma once
#include <atomic>
#include "EngineProtocol.h"
#include "EngineNet.h"

// 설명 :
class UNetObject
{
public:
	UNetObject();
	~UNetObject();

	// delete Function
	UNetObject(const UNetObject& _Other) = delete;
	UNetObject(UNetObject&& _Other) noexcept = delete;
	UNetObject& operator=(const UNetObject& _Other) = delete;
	UNetObject& operator=(UNetObject&& _Other) noexcept = delete;

	static int GetNewObjectToken()
	{
		return ++CurObjectToken;
	}

	void InitNet(std::shared_ptr<UEngineNet> _Net)
	{
		Net = _Net;
	}

	// net을 받아야 
	bool IsNetInit()
	{
		return Net != nullptr;
	}

	void Send(std::shared_ptr<UEngineProtocol> _Protocol);

protected:
	static std::atomic<int> CurObjectToken;

private:
	std::shared_ptr<UEngineNet> Net = nullptr;
	// -1이면 안받은애이다.
	std::atomic<int> Token = -1;

};

