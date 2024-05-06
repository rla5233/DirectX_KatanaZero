#pragma once
#include "EngineSerializer.h"

// 설명 : 내가 뭔지는 중요하지 않다. 

class UEngineNet
{
public:
	// constrcuter destructer
	UEngineNet();
	~UEngineNet();

	// delete Function
	UEngineNet(const UEngineNet& _Other) = delete;
	UEngineNet(UEngineNet&& _Other) noexcept = delete;
	UEngineNet& operator=(const UEngineNet& _Other) = delete;
	UEngineNet& operator=(UEngineNet&& _Other) noexcept = delete;

	//virtual void Send(UEngineSerializer& _Data);
	//virtual void Recv(UEngineSerializer& _Data);

	//virtual void Send(void* _Ptr, int _Size);
	//virtual void Recv(void* _Ptr, int _Size);

	virtual void ServerOpen(int _Port, int _BackLog)	{	}

	// virtual void Connect();

protected:

private:

};

